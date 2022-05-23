#include "Renderer.hpp"

#include <cassert>

Renderer::Renderer(Color* buffer, int height, int width)
    : buffer_(buffer),
      height_(height),
      width_(width),
      color_(kWhite) {
  assert(buffer_);
}

int Renderer::Index(int x, int y) {
  if (!(0 <= x && x < width_ && 0 <= y && y < height_)) {
    return 0;
  }
  
  return y * width_ + x;
}

int Renderer::GetWidth() const {
  return width_;
}

int Renderer::GetHeight() const {
  return height_;
}

void Renderer::SetColor(Color color) {
  color_ = color;
}


void Renderer::FillRect(int x0, int y0, int size_x, int size_y) {
  assert(buffer_);

  for (int x = x0; x < x0 + size_x; ++x) {
    for (int y = y0; y < y0 + size_y; ++y) {
      buffer_[Index(x, y)] = color_;
    }
  }
}

void Renderer::DrawRect(int x0, int y0, int size_x, int size_y) {
  assert(buffer_);

  for (int x = x0; x < x0 + size_x; ++x) {
    buffer_[Index(x, y0)] = color_;
    buffer_[Index(x, y0 + size_y)] = color_;
  }

  for (int y = y0; y < y0 + size_y; ++y) {
    buffer_[Index(x0, y)] = color_;
    buffer_[Index(x0 + size_x, y)] = color_;
  }
}

void Renderer::DrawLine(int x0, int y0, int x1, int y1) {
  assert(buffer_);

  int dx = abs(x1 - x0);
  int step_x = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int step_y = y0 < y1 ? 1 : -1;
  int error = dx + dy;
  
  while (x0 != x1 || y0 != y1) {
    buffer_[Index(x0, y0)] = color_;

    if (2 * error >= dy) {
      if (x0 == x1) {
        break;
      }

      error = error + dy;
      x0 = x0 + step_x;
    }

    if (2 * error <= dx) {
        if (y0 == y1) {
          break;
        }
        
        error = error + dx;
        y0 = y0 + step_y;
    }
  }
}

void Renderer::DrawCircle(int x0, int y0, int radius) {
  assert(buffer_);

  float angle_step = 1 / (2 * M_PI * radius);

  for (float angle = 0; angle < M_PI / 2; angle += angle_step) {
    int dx = std::round(std::cos(angle) * radius);
    int dy = std::round(std::sin(angle) * radius);

    buffer_[Index(x0 + dx, y0 + dy)] = color_;
    buffer_[Index(x0 + dx, y0 - dy)] = color_;
    buffer_[Index(x0 - dx, y0 + dy)] = color_;
    buffer_[Index(x0 - dx, y0 - dy)] = color_;
  }
}

void Renderer::FillCircle(int x0, int y0, int radius) {
  assert(buffer_);

  float angle_step = 1 / (2 * M_PI * radius);

  for (float angle = 0; angle < M_PI / 2; angle += angle_step) {
    int dx = std::round(std::cos(angle) * radius);
    int dy = std::round(std::sin(angle) * radius);

    for (int x = x0 - dx; x < x0 + dx; ++x) {
      buffer_[Index(x , y0 + dy)] = color_;
      buffer_[Index(x , y0 - dy)] = color_;
    }
  }
}
