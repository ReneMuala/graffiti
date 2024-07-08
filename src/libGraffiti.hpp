#pragma once
#include <blend2d.h>
#include <sol/sol.hpp>

/**
 * @brief Graffiti native API functions
 *
 */
namespace _graffiti_native {
void show_version();
unsigned long long new_image(double width, double height);
double unit_pixel(double value);
double unit_cm(double value);
double get_width();
double get_height();
unsigned long long gg(int depth);
void context_export(unsigned long long native_index, std::string filename);
void context_fill_i32(unsigned long long native_index, int i32);
void context_rect(unsigned long long native_index, double x, double y, double w,
                  double h);
void context_circle(unsigned long long native_index, double cx, double cy,
                    double r);
void context_stroke_i32(unsigned long long native_index, int color, double width, int startcap, int endcap, int join);
void context_close();
void context_text(unsigned long long native_index, double x, double y,
                  std::string text, double size, std::string font);
void context_box(unsigned long long native_index, double x0, double y0,
                 double x1, double y1);
void context_line(unsigned long long native_index, double x0, double y0,
                  double x1, double y1);
void context_arc(unsigned long long native_index, double cx, double cy,
                 double rx, double ry, double start, double sweep);
void context_chord(unsigned long long native_index, double cx, double cy,
                   double rx, double ry, double start, double sweep);
void context_pie(unsigned long long native_index, double cx, double cy,
                 double rx, double ry, double start, double sweep);
void context_roundrect_1(unsigned long long native_index, double x, double y,
                         double w, double h, double r);
void context_roundrect_2(unsigned long long native_index, double x, double y,
                         double w, double h, double rx, double ry);
void context_triangle(unsigned long long native_index, double x0, double y0,
                      double x1, double y1, double x2, double y2);
void context_ellipse(unsigned long long native_index, double cx, double cy,
                     double r);
void context_arcTo(unsigned long long native_index, double cx, double cy,
                   double rx, double ry, double start, double sweep);
void context_conicTo(unsigned long long native_index, double x0, double y0,
                     double x1, double y1, double w);
void context_cubicTo(unsigned long long native_index, double x0, double y0,
                     double x1, double y1, double x2, double y2);
void context_lineTo(unsigned long long native_index, double x0, double y0);
void context_moveTo(unsigned long long native_index, double x0, double y0);
void context_quadTo(unsigned long long native_index, double x0, double y0,
                    double x1, double y1);
void context_arcQuadrantTo(unsigned long long native_index, double x0,
                           double y0, double x1, double y1);
void context_ellipticArcTo(unsigned long long native_index, double rx,
                           double ry, double xAxisRotation, bool largeArcFlag,
                           bool sweepFlag, double x1, double y1);
void context_smoothCubicTo(unsigned long long native_index, double x0,
                           double y0, double x1, double y1);
void context_smoothQuadTo(unsigned long long native_index, double x0,
                          double y0);
unsigned long long new_linear_gradient(double x0, double y0, double x1, double y1);
unsigned long long new_radial_gradient(double x0, double y0, double x1, double y1, double r);
void gradient_step(unsigned long long native_index, double pct, int color);
void context_fill_gradient(unsigned long long native_index, unsigned long long gradient_native_index);
void context_stroke_gradient(unsigned long long native_index, unsigned long long gradient_native_index, double width, int startcap, int endcap, int join);
void context_fill_context(unsigned long long native_index, unsigned long long context_native_index);
void context_stroke_context(unsigned long long native_index, unsigned long long context_native_index, double width, int startcap, int endcap, int join);
void context_fill_i32_rect(unsigned long long native_index, int i32,double x, double y, double w, double h);
void context_fill_gradient_rect(unsigned long long native_index, unsigned long long gradient_native_index, double x, double y, double w, double h);
void context_fill_context_rect(unsigned long long native_index, unsigned long long context_native_index, double x, double y, double w, double h);
void context_rotate(unsigned long long native_index, double angle, double cx, double cy);
void context_resize(unsigned long long native_index, double x, double y);
void context_translate(unsigned long long native_index, double x, double y);
void context_closepath(unsigned long long native_index);
void context_import(unsigned long long native_index,std::string filename); // v1.1
} // namespace _graffiti_native

void resolveGraffitiLibrary(sol::state &lua);
