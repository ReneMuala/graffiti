#include "libGraffiti.hpp"
#include "Context.hpp"
#include "Font.hpp"
#include "Gradient.hpp"
#include "Version.hpp"
#include "sol/forward.hpp"
#include "sol/optional_implementation.hpp"
#include <deque>
#include <format>
#include <functional>
#include <map>
#include <memory>
#include <stdexcept>

/**
 * @brief Graffiti native API functions
 *
 */
namespace _graffiti_native {
namespace data {
double width = 1, height = 1;
std::deque<std::shared_ptr<Context>> contexts;
std::deque<std::shared_ptr<Gradient>> gradients;
std::map<std::string, std::shared_ptr<Font>> fonts;
} // namespace data
void show_version() {
  std::cout << GRAFFITI_VERSION << " ( Blend2d " << BL_VERSION << " "
            << LUA_VERSION << " )" << std::endl;
}

inline double resolveValue(double value) {
  return (value * data::width) / 100.0;
}

unsigned long long new_image(double width, double height) {
  if (data::width != 1 || data::height != 1) {
    throw std::runtime_error(std::format(
        "{}: {}", __FUNCTION__,
        "Unsafe operation, call .close() before creating a new image"));
  }

  width /= 100;
  height /= 100;
  data::contexts.push_back(std::make_shared<Context>(width, height));
  data::width = width;
  data::height = height;
  // std::cout << __FUNCTION__ << std::endl;
  return (unsigned long long)data::contexts.back().get();
}

double unit_pixel(double value) { return (value / data::width) * 100; }

double unit_cm(double value) { return unit_pixel(value) * 37.795275591; }

double get_width() { return data::width; }

double get_height() { return data::height; }

unsigned long long gg(int depth) {
  if (data::contexts.empty()) {
    throw std::runtime_error(
        std::format("{}: {}", __FUNCTION__, "No context available"));
  }
  std::shared_ptr<Context> context_ptr;
  for (int i = 0; i < depth; i++) {
    if (i == 0) {
      context_ptr = data::contexts.back();
    } else {
      context_ptr = context_ptr.get()->getChild();
    }
  }
  context_ptr->resolveChild();
  return (unsigned long long)(context_ptr.get());
}

void context_export(unsigned long long native_index, std::string filename) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->_export(filename);
}

void context_fill_i32(unsigned long long native_index, int i32) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_i32(i32);
}

void context_rect(unsigned long long native_index, double x, double y, double w,
                  double h) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->rect(resolveValue(x), resolveValue(y), resolveValue(w),
                  resolveValue(h));
}

void context_circle(unsigned long long native_index, double cx, double cy,
                    double r) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->circle(resolveValue(cx), resolveValue(cy), resolveValue(r));
}

void context_stroke_i32(unsigned long long native_index, int color,
                        double width, int startcap, int endcap, int join) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->stroke_i32(color, resolveValue(width), startcap, endcap, join);
}

void context_close() {
  data::width = 1;
  data::height = 1;
}

std::string font(std::string filename) {
  if (not data::fonts.count(filename))
    data::fonts[filename] = std::make_shared<Font>(filename);
  return filename;
}

void context_text(unsigned long long native_index, double x, double y,
                  std::string text, double size, std::string font) {
  std::shared_ptr<Font> choosenFont = data::fonts[font];
  if (not choosenFont) {
    throw std::runtime_error(
        std::format("{}: {} \"{}\"", __FUNCTION__, "Invalid font", font));
  }
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->text(resolveValue(x), resolveValue(y), text, resolveValue(size),
                  choosenFont);
}

//////

void context_box(unsigned long long native_index, double x0, double y0,
                 double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->box(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                 resolveValue(y1));
}

void context_line(unsigned long long native_index, double x0, double y0,
                  double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->line(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                  resolveValue(y1));
}

void context_arc(unsigned long long native_index, double cx, double cy,
                 double rx, double ry, double start, double sweep) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->arc(resolveValue(cx), resolveValue(cy), resolveValue(rx),
                 resolveValue(ry), start, sweep);
}

void context_chord(unsigned long long native_index, double cx, double cy,
                   double rx, double ry, double start, double sweep) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->chord(resolveValue(cx), resolveValue(cy), resolveValue(rx),
                   resolveValue(ry), start, sweep);
}

void context_pie(unsigned long long native_index, double cx, double cy,
                 double rx, double ry, double start, double sweep) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->pie(resolveValue(cx), resolveValue(cy), resolveValue(rx),
                 resolveValue(ry), start, sweep);
}

void context_roundrect_1(unsigned long long native_index, double x, double y,
                         double w, double h, double r) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->roundrect(resolveValue(x), resolveValue(y), resolveValue(w),
                       resolveValue(h), resolveValue(r));
}

void context_roundrect_2(unsigned long long native_index, double x, double y,
                         double w, double h, double rx, double ry) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->roundrect(resolveValue(x), resolveValue(y), resolveValue(w),
                       resolveValue(h), resolveValue(rx), resolveValue(ry));
}

void context_triangle(unsigned long long native_index, double x0, double y0,
                      double x1, double y1, double x2, double y2) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->triangle(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                      resolveValue(y1), resolveValue(x2), resolveValue(y2));
}

void context_ellipse(unsigned long long native_index, double cx, double cy,
                     double r) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->ellipse(resolveValue(cx), resolveValue(cy), resolveValue(r));
}

void context_arcTo(unsigned long long native_index, double cx, double cy,
                   double rx, double ry, double start, double sweep) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->arcTo(resolveValue(cx), resolveValue(cy), resolveValue(rx),
                   resolveValue(ry), start, sweep);
}

void context_conicTo(unsigned long long native_index, double x0, double y0,
                     double x1, double y1, double w) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->conicTo(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                     resolveValue(y1), resolveValue(w));
}

void context_cubicTo(unsigned long long native_index, double x0, double y0,
                     double x1, double y1, double x2, double y2) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->cubicTo(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                     resolveValue(y1), resolveValue(x2), resolveValue(y2));
}

void context_lineTo(unsigned long long native_index, double x0, double y0) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->lineTo(resolveValue(x0), resolveValue(y0));
}

void context_moveTo(unsigned long long native_index, double x0, double y0) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->moveTo(resolveValue(x0), resolveValue(y0));
}

void context_quadTo(unsigned long long native_index, double x0, double y0,
                    double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->quadTo(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                    resolveValue(y1));
}

void context_arcQuadrantTo(unsigned long long native_index, double x0,
                           double y0, double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->arcQuadrantTo(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                           resolveValue(y1));
}

void context_ellipticArcTo(unsigned long long native_index, double rx,
                           double ry, double xAxisRotation, bool largeArcFlag,
                           bool sweepFlag, double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->ellipticArcTo(resolveValue(rx), resolveValue(ry), xAxisRotation,
                           largeArcFlag, sweepFlag, resolveValue(x1),
                           resolveValue(y1));
}

void context_smoothCubicTo(unsigned long long native_index, double x0,
                           double y0, double x1, double y1) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->smoothCubicTo(resolveValue(x0), resolveValue(y0), resolveValue(x1),
                           resolveValue(y1));
}

void context_smoothQuadTo(unsigned long long native_index, double x0,
                          double y0) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->smoothQuadTo(resolveValue(x0), resolveValue(y0));
}

unsigned long long new_linear_gradient(double x0, double y0, double x1,
                                       double y1) {
  if (data::width != 1 || data::height != 1) {
    throw std::runtime_error(std::format(
        "{}: {}", __FUNCTION__,
        "Unsafe operation, call .close() before creating a new gradient"));
  }
  std::shared_ptr<Gradient> gradient = std::make_shared<Gradient>(
      std::vector<double>{x0, y0, x1, y1}, resolveValue);
  data::gradients.push_back(gradient);
  return (unsigned long long)gradient.get();
}

unsigned long long new_radial_gradient(double x0, double y0, double x1,
                                       double y1, double r) {
  if (data::width != 1 || data::height != 1) {
    throw std::runtime_error(std::format(
        "{}: {}", __FUNCTION__,
        "Unsafe operation, call .close() before creating a new gradient"));
  }
  std::shared_ptr<Gradient> gradient = std::make_shared<Gradient>(
      std::vector<double>{x0, y0, x1, y1, r}, resolveValue);
  data::gradients.push_back(gradient);
  return (unsigned long long)gradient.get();
}

void gradient_step(unsigned long long native_index, double pct, int color) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid gradient native_index",
                                         native_index));
  }
  Gradient *gradient = (Gradient *)native_index;
  gradient->step(pct, color);
}

void context_fill_gradient(unsigned long long native_index,
                           unsigned long long gradient_native_index) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not gradient_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid gradient native_index",
                                         gradient_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_gradient((Gradient *)gradient_native_index);
}

void context_stroke_gradient(unsigned long long native_index,
                             unsigned long long gradient_native_index,
                             double width, int startcap, int endcap, int join) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not gradient_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid gradient native_index",
                                         gradient_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->stroke_gradient((Gradient *)gradient_native_index,
                             resolveValue(width), startcap, endcap, join);
}

void context_fill_context(unsigned long long native_index,
                          unsigned long long context_native_index) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not context_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid source context native_index",
                                         context_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_context((Context *)context_native_index);
}

void context_stroke_context(unsigned long long native_index,
                            unsigned long long context_native_index,
                            double width, int startcap, int endcap, int join) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not context_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid source context native_index",
                                         context_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->stroke_context((Context *)context_native_index,
                            resolveValue(width), startcap, endcap, join);
}

void context_fill_i32_rect(unsigned long long native_index, int i32, double x,
                           double y, double w, double h) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_i32_rect(i32, resolveValue(x), resolveValue(y),
                           resolveValue(w), resolveValue(h));
}

void context_fill_gradient_rect(unsigned long long native_index,
                                unsigned long long gradient_native_index,
                                double x, double y, double w, double h) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not gradient_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid gradient native_index",
                                         gradient_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_gradient_rect((Gradient *)gradient_native_index,
                                resolveValue(x), resolveValue(y),
                                resolveValue(w), resolveValue(h));
}

void context_fill_context_rect(unsigned long long native_index,
                               unsigned long long context_native_index,
                               double x, double y, double w, double h) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  if (not context_native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid source context native_index",
                                         context_native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->fill_context_rect((Context *)context_native_index, resolveValue(x),
                               resolveValue(y), resolveValue(w),
                               resolveValue(h));
}

void context_rotate(unsigned long long native_index, double angle, double cx,
                    double cy) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->rotate(angle, resolveValue(cx), resolveValue(cy));
}

void context_resize(unsigned long long native_index, double x, double y) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->resize(x, y);
}

void context_translate(unsigned long long native_index, double x, double y) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->translate(resolveValue(x), resolveValue(y));
}

void context_closepath(unsigned long long native_index) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->closePath();
}

void context_import(unsigned long long native_index, std::string filename) {
  if (not native_index) {
    throw std::runtime_error(std::format("{}: {} {}", __FUNCTION__,
                                         "Invalid context native_index",
                                         native_index));
  }
  Context *context_p = (Context *)(native_index);
  context_p->_import(filename);
}
} // namespace _graffiti_native

void resolveGraffitiLibrary(sol::state &lua) {
  lua.set_function("_graffiti_native_new_image", _graffiti_native::new_image);
  lua.set_function("_graffiti_native_show_version",
                   _graffiti_native::show_version);
  lua.set_function("_graffiti_native_unit_pixel", _graffiti_native::unit_pixel);
  lua.set_function("_graffiti_native_unit_cm", _graffiti_native::unit_cm);
  lua.set_function("_graffiti_native_get_width", _graffiti_native::get_width);
  lua.set_function("_graffiti_native_get_height", _graffiti_native::get_height);
  lua.set_function("_graffiti_native_gg", _graffiti_native::gg);
  lua.set_function("_graffiti_native_context_export",
                   _graffiti_native::context_export);
  lua.set_function("_graffiti_native_context_fill_i32",
                   _graffiti_native::context_fill_i32);
  lua.set_function("_graffiti_native_context_rect",
                   _graffiti_native::context_rect);
  lua.set_function("_graffiti_native_context_circle",
                   _graffiti_native::context_circle);
  lua.set_function("_graffiti_native_context_stroke_i32",
                   _graffiti_native::context_stroke_i32);
  lua.set_function("_graffiti_native_context_close",
                   _graffiti_native::context_close);
  lua.set_function("_graffiti_native_font", _graffiti_native::font);
  lua.set_function("_graffiti_native_context_text",
                   _graffiti_native::context_text);

  lua.set_function("_graffiti_native_context_box",
                   _graffiti_native::context_box);
  lua.set_function("_graffiti_native_context_line",
                   _graffiti_native::context_line);
  lua.set_function("_graffiti_native_context_arc",
                   _graffiti_native::context_arc);
  lua.set_function("_graffiti_native_context_chord",
                   _graffiti_native::context_chord);
  lua.set_function("_graffiti_native_context_pie",
                   _graffiti_native::context_pie);
  lua.set_function("_graffiti_native_context_roundrect_1",
                   _graffiti_native::context_roundrect_1);
  lua.set_function("_graffiti_native_context_roundrect_2",
                   _graffiti_native::context_roundrect_2);
  lua.set_function("_graffiti_native_context_triangle",
                   _graffiti_native::context_triangle);
  lua.set_function("_graffiti_native_context_ellipse",
                   _graffiti_native::context_ellipse);

  lua.set_function("_graffiti_native_context_arcTo",
                   _graffiti_native::context_arcTo);
  lua.set_function("_graffiti_native_context_conicTo",
                   _graffiti_native::context_conicTo);
  lua.set_function("_graffiti_native_context_cubicTo",
                   _graffiti_native::context_cubicTo);
  lua.set_function("_graffiti_native_context_lineTo",
                   _graffiti_native::context_lineTo);
  lua.set_function("_graffiti_native_context_moveTo",
                   _graffiti_native::context_moveTo);
  lua.set_function("_graffiti_native_context_quadTo",
                   _graffiti_native::context_quadTo);

  lua.set_function("_graffiti_native_context_arcQuadrantTo",
                   _graffiti_native::context_arcQuadrantTo);

  lua.set_function("_graffiti_native_context_ellipticArcTo",
                   _graffiti_native::context_ellipticArcTo);

  lua.set_function("_graffiti_native_context_smoothCubicTo",
                   _graffiti_native::context_smoothCubicTo);

  lua.set_function("_graffiti_native_context_smoothQuadTo",
                   _graffiti_native::context_smoothQuadTo);

  lua.set_function("_graffiti_native_new_linear_gradient",
                   _graffiti_native::new_linear_gradient);
  lua.set_function("_graffiti_native_new_radial_gradient",
                   _graffiti_native::new_radial_gradient);
  lua.set_function("_graffiti_native_gradient_step",
                   _graffiti_native::gradient_step);

  lua.set_function("_graffiti_native_context_fill_gradient",
                   _graffiti_native::context_fill_gradient);
  lua.set_function("_graffiti_native_context_stroke_gradient",
                   _graffiti_native::context_stroke_gradient);

  lua.set_function("_graffiti_native_context_fill_context",
                   _graffiti_native::context_fill_context);
  lua.set_function("_graffiti_native_context_stroke_context",
                   _graffiti_native::context_stroke_context);

  lua.set_function("_graffiti_native_context_fill_i32_rect",
                   _graffiti_native::context_fill_i32_rect);
  lua.set_function("_graffiti_native_context_fill_gradient_rect",
                   _graffiti_native::context_fill_gradient_rect);
  lua.set_function("_graffiti_native_context_fill_context_rect",
                   _graffiti_native::context_fill_context_rect);

  lua.set_function("_graffiti_native_context_rotate",
                   _graffiti_native::context_rotate);
  lua.set_function("_graffiti_native_context_resize",
                   _graffiti_native::context_resize);
  lua.set_function("_graffiti_native_context_translate",
                   _graffiti_native::context_translate);
  lua.set_function("_graffiti_native_context_closepath",
                   _graffiti_native::context_closepath);
  lua.set_function("_graffiti_native_context_import",
                   _graffiti_native::context_import);
}

/*


  std::reference_wrapper<std::shared_ptr<Context>> context_ptr =
  data::contexts.back(); bool first_iteration = true; for (int i = 0; i < depth;
  i++) { if (first_iteration) { first_iteration = false; } else { context_ptr =
  context_ptr.get()->getChild();
    }
  }
  context_ptr.get()->child = NULL;
  // context_ptr.get()->resolveChild();
  // std::cout << ">> " << context_ptr->child << std::endl;
  return (unsigned long long)(context_ptr.get().get());
*/