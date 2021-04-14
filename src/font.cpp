#include <font.hpp>
#include <numeric>

font::font(const font_loader& font)
  : font_tex_("rsrc/" + font.get_page_filenames().front())
{
  //float x y u v
  std::vector<float> font_data_for_gpu;
  const auto tex_size = font.get_texture_size();
  for (const auto& elem : font.get_char_details())
  {
    unsigned index = char_id_to_vbo_index_.size();
    char_id_to_vbo_index_[elem.id] = index;
    offset_data_.push_back(elem.xadvance);

    float u_left = elem.x;
    float u_right = elem.x + elem.width;
    float v_top = elem.y;
    float v_bot = elem.y + elem.height;
    u_left /= tex_size;
    u_right /= tex_size;
    v_top /= tex_size;
    v_bot /= tex_size;

    float x_left = (float)elem.xoffset;
    float x_right = x_left + (float)elem.width;
    float y_top = (float)elem.yoffset;
    float y_bot = y_top + (float)elem.height;

    //left bottom
    font_data_for_gpu.push_back(x_left);
    font_data_for_gpu.push_back(y_bot);
    font_data_for_gpu.push_back(u_left);
    font_data_for_gpu.push_back(v_bot);
    //left upper
    font_data_for_gpu.push_back(x_left);
    font_data_for_gpu.push_back(y_top);
    font_data_for_gpu.push_back(u_left);
    font_data_for_gpu.push_back(v_top);
    //right bottom
    font_data_for_gpu.push_back(x_right);
    font_data_for_gpu.push_back(y_bot);
    font_data_for_gpu.push_back(u_right);
    font_data_for_gpu.push_back(v_bot);
    //right upper
    font_data_for_gpu.push_back(x_right);
    font_data_for_gpu.push_back(y_top);
    font_data_for_gpu.push_back(u_right);
    font_data_for_gpu.push_back(v_top);

  }
  glGenVertexArrays(1, &VAO_);
  glBindVertexArray(VAO_);
  glGenBuffers(1, &VBO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, font_data_for_gpu.size() * sizeof(float), font_data_for_gpu.data(), GL_STATIC_DRAW);

  //pos
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //uv
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

font::~font()
{
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
}

const texture& font::get_font_tex() const
{
  return font_tex_;
}

unsigned font::char_id_to_vbo_index(unsigned char_id) const
{
  if (char_id_to_vbo_index_.count(char_id) == 0)
    return 0xFFFFFFFF;
  return char_id_to_vbo_index_.at(char_id);
}

float font::get_advancement(unsigned char_id) const
{
  return offset_data_[char_id_to_vbo_index_.at(char_id)];
}

void font::bind() const
{
  glBindVertexArray(VAO_);
}

int font::get_text_size(const std::string& text) const
{
  return std::accumulate(text.begin(), text.end(), 0, [this](int acc, char elem)
  {
    auto my_index = char_id_to_vbo_index_.at(elem);
    return acc + (int)offset_data_[my_index];
  });
}
