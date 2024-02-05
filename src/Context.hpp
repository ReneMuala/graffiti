#pragma once

#include "Gradient.hpp"
#include "TextPath.hpp"
#include <blend2d.h>
#include <blend2d/geometry.h>
#include <blend2d/gradient.h>
#include <blend2d/path.h>
#include <blend2d/pattern.h>
#include <blend2d/rgba.h>
#include <blend2d/var.h>
#include <cassert>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>

class Context {
  BLImage image;
  BLContext context;
  BLPath path;
  std::optional<std::reference_wrapper<Context>> super;
  std::deque<TextPath> tpaths;

public:
  std::shared_ptr<Context> child;

  Context(int width, int height,
          std::optional<std::reference_wrapper<Context>> super = {})
      : super(super), image(width, height, BL_FORMAT_PRGB32), context(image),
        child(nullptr) {
    context.clearAll();
    // std::cout << __FUNCTION__ << " | new context " << width << " x " << height
              // << std::endl;
  }
  void clearContext() { context.clearAll(); }
  /// binds the child context to the super
  void resolveChild(bool strokeResolution = false) {
    if (child) {
      child->resolveChild(strokeResolution);
      auto pattern = BLPattern(child->image);
      if (path.empty() and tpaths.empty())
        context.fillAll(pattern);
      else {
        context.fillPath(path, pattern);
        for (auto &tpath : tpaths) {
          tpath.fill(context, pattern);
        }
      }
      if (not strokeResolution) {
        path.clear();
        child.reset();
      } else {
        child->clearContext();
      }
    }
  }

  std::shared_ptr<Context> &getChild() {
    if (not child) {
      child = std::make_shared<Context>(image.width(), image.height(), *this);
    }
    return child;
  }

  void _export(std::string filename) { image.writeToFile(filename.c_str()); }

  inline void box(double x0, double y0, double x1, double y1) {
    path.addBox(x0, y0, x1, y1);
  }

  inline void line(double x0, double y0, double x1, double y1) {
    path.addLine(BLLine(x0, y0, x1, y1));
  }

  inline void arc(double cx, double cy, double rx, double ry, double start,
                  double sweep) {
    path.addArc(BLArc(cx, cy, rx, ry, start, sweep));
  }

  inline void chord(double cx, double cy, double rx, double ry, double start,
                    double sweep) {
    path.addChord(BLArc(cx, cy, rx, ry, start, sweep));
  }

  inline void pie(double cx, double cy, double rx, double ry, double start,
                  double sweep) {
    path.addPie(BLArc(cx, cy, rx, ry, start, sweep));
  }

  inline void roundrect(double x, double y, double w, double h, double r) {
    path.addRoundRect(BLRoundRect(x, y, w, h, r));
  }

  inline void roundrect(double x, double y, double w, double h, double rx,
                        double ry) {
    path.addRoundRect(BLRoundRect(x, y, w, h, rx, ry));
  }

  inline void triangle(double x0, double y0, double x1, double y1, double x2,
                       double y2) {
    path.addTriangle(BLTriangle(x0, y0, x1, y1, x2, y2));
  }

  inline void rect(double x, double y, double w, double h) {
    path.addRect(x, y, w, h);
  }

  inline void circle(double cx, double cy, double r) {
    path.addCircle(BLCircle(cx, cy, r));
  }

  inline void ellipse(double cx, double cy, double r) {
    path.addEllipse(BLEllipse(cx, cy, r));
  }

  ////

  inline void arcTo(double cx, double cy, double rx, double ry, double start,
                    double sweep) {
    path.arcTo(cx, cy, rx, ry, start, sweep);
  }

  inline void conicTo(double x0, double y0, double x1, double y1, double w) {
    path.conicTo(x0, y0, x1, y1, w);
  }

  inline void cubicTo(double x0, double y0, double x1, double y1, double x2,
                      double y2) {
    path.cubicTo(x0, y0, x1, y1, x2, y2);
  }

  inline void lineTo(double x0, double y0) { path.lineTo(x0, y0); }

  inline void moveTo(double x0, double y0) { path.moveTo(x0, y0); }

  inline void quadTo(double x0, double y0, double x1, double y1) {
    path.quadTo(x0, y0, x1, y1);
  }

  inline void arcQuadrantTo(double x0, double y0, double x1, double y1) {
    path.arcQuadrantTo(x0, y0, x1, y1);
  }

  inline void ellipticArcTo(double rx, double ry, double xAxisRotation,
                            bool largeArcFlag, bool sweepFlag, double x1,
                            double y1) {
    path.ellipticArcTo(rx, ry, xAxisRotation, largeArcFlag, sweepFlag, x1, y1);
  }

  inline void smoothCubicTo(double x0, double y0, double x1, double y1) {
    path.smoothCubicTo(x0, y0, x1, y1);
  }

  inline void smoothQuadTo(double x0, double y0) { path.smoothQuadTo(x0, y0); }

  inline void text(double x, double y, std::string text, double size,
                   std::shared_ptr<Font> font) {
    tpaths.push_back(TextPath(text, font, size, x, y));
  }

  inline void closePath() { path.close(); }

  inline void resetStrokeStyle() { context.setStrokeWidth(1); }

  inline void setStrokeWidth(double width) {
    context.setStrokeWidth(width);
    context.setStrokeStartCap((BLStrokeCap)0);
    context.setStrokeEndCap((BLStrokeCap)0);
    context.setStrokeJoin((BLStrokeJoin)0);
  }

  inline void setStrokeStartCap(int val) {
    context.setStrokeStartCap((BLStrokeCap)val);
  }

  inline void setStrokeEndCap(int val) {
    context.setStrokeEndCap((BLStrokeCap)val);
  }

  inline void setStrokeJoin(int val) {
    context.setStrokeJoin((BLStrokeJoin)val);
  }

  template <typename pattern_t>
  inline void stroke(pattern_t pattern, double width, int startcap, int endcap,
                     int join) {
    if (super and (super->get().path.size() or super->get().tpaths.size())) {
      super->get().resolveChild(true);
      super->get().setStrokeWidth(width);
      super->get().setStrokeStartCap(startcap);
      super->get().setStrokeEndCap(endcap);
      super->get().setStrokeJoin(join);

      super->get().context.strokePath(super->get().path, pattern);
      for (auto &tpath : super->get().tpaths) {
        // std::cout << "stroke txt << \n";
        tpath.stroke(super->get().context, pattern);
      }
      super->get().resetStrokeStyle();
    } else {
      std::cerr << __FUNCTION__ << ": No enough contitions for stroke\n";
    }
  }

  inline void stroke_i32(int color, double width, int startcap, int endcap,
                         int join) {
    stroke(BLRgba32(color), width, startcap, endcap, join);
  }

  inline void stroke_gradient(Gradient *gradient, double width, int startcap,
                              int endcap, int join) {
    assert(gradient != NULL);
    stroke(gradient->build(), width, startcap, endcap, join);
  }

  inline void stroke_context(Context *context, double width, int startcap,
                             int endcap, int join) {
    assert(context != NULL);
    context->resolveChild(true);
    stroke(BLPattern(context->image), width, startcap, endcap, join);
  }

  template <typename pattern_t> inline void fill(pattern_t pattern) {
    context.fillAll(pattern);
  }

  inline void fill_i32(int color) { fill(BLRgba32(color)); }

  inline void fill_gradient(Gradient *gradient) {
    assert(gradient != NULL);
    fill(gradient->build());
  }

  inline void fill_context(Context *context) {
    assert(context != NULL);
    context->resolveChild(true);
    fill(BLPattern(context->image));
  }

  template <typename pattern_t>
  inline void fill_rect(pattern_t pattern, BLRect rect) {
    context.blitImage(rect, pattern);
  }

  inline void fill_rect(BLRgba32 pattern, BLRect rect) {
    context.fillRect(rect, pattern);
  }

  inline void fill_rect(BLGradient pattern, BLRect rect) {
    context.fillRect(rect, pattern);
  }

  inline void fill_i32_rect(int color, double x, double y, double w, double h) {
    fill_rect(BLRgba32(color), BLRect(x, y, w, h));
  }

  inline void fill_gradient_rect(Gradient *gradient, double x, double y,
                                 double w, double h) {
    assert(gradient != NULL);
    fill_rect(gradient->build(), BLRect(x, y, w, h));
  }

  inline void rotate(double angle, double cx, double cy) {
    context.rotate(angle, cx, cy);
  }

  inline void resize(double x, double y) { context.scale(x, y); }
  
  inline void translate(double x, double y) { context.translate(x, y); }

  inline void fill_context_rect(Context *context, double x, double y, double w,
                                double h) {
    assert(context != NULL);
    context->resolveChild(true);
    fill_rect(context->image, BLRect(x, y, w, h));
  }
};