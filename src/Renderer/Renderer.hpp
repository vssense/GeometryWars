#ifndef _RENDERER_HPP_INCLUDED
#define _RENDERER_HPP_INCLUDED

#include <cstdint>
#include <cmath>

#include "Color.hpp"

class Renderer {
 public:
  Renderer(Color* buffer, int height, int width);

  int GetWidth() const;
  int GetHeight() const;

  void SetColor(Color color);

  int Index(int x, int y);

  void DrawLine(int x0, int y0, int x1, int y1);
  void DrawRect(int x0, int y0, int size_x, int size_y);
  void FillRect(int x0, int y0, int size_x, int size_y);

  void DrawCircle(int x, int y, int radius);
  void FillCircle(int x, int y, int radius);

 private:
  Color* buffer_;

  int height_;
  int width_;

  Color color_;
};

#endif // _RENDERER_HPP_INCLUDED
