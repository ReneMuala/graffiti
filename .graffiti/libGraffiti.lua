unit = {}

unit.__index = unit

function unit:pixel(size)
    return _graffiti_native_unit_pixel(size)
end

function unit:cm(size)
    return _graffiti_native_unit_cm(size)
end


function unit:deg(size)
    return size * 3.14159265359 / 180.0
end

---@param x number
---@param y number
function point(x, y)
    return {
        type = "point",
        x = x,
        y = y
    }
end

GraffitiContext = {}
GraffitiContext.__index = GraffitiContext
gc = GraffitiContext
---@param width number
---@param height number
function gc:new(width, height, native_index)
    local g = {
        type = "context",
        native_index = native_index or _graffiti_native_new_image(width, height),
        width = width,
        height = height
    }
    -- print("native_index: ", g.native_index)
    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    g.box = function(x0, y0, x1, y1)
        _graffiti_native_context_box(g.native_index, x0, y0, x1, y1)
        return g
    end

    ---@param cx number
    ---@param cy number
    ---@param rx number
    ---@param ry number
    ---@param start number
    ---@param sweep number
    g.chord = function(cx, cy, rx, ry, start, sweep)
        _graffiti_native_context_chord(g.native_index, cx, cy, rx, ry, start, sweep)
        return g
    end

    ---@param x number
    ---@param y number
    ---@param r number
    g.circle = function(x, y, r)
        _graffiti_native_context_circle(g.native_index, x, y, r)
        return g
    end

    ---@param cx number
    ---@param cy number
    ---@param r number
    g.ellipse = function(cx, cy, r)
        _graffiti_native_context_ellipse(g.native_index, cx, cy, r)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    g.line = function(x0, y0, x1, y1)
        _graffiti_native_context_line(g.native_index, x0, y0, x1, y1)
        return g
    end

    ---@param cx number
    ---@param cy number
    ---@param rx number
    ---@param ry number
    ---@param start number
    ---@param sweep number
    g.pie = function(cx, cy, rx, ry, start, sweep)
        _graffiti_native_context_pie(g.native_index, cx, cy, rx, ry, start, sweep)
        return g
    end

    ---@param x number
    ---@param y number
    ---@param w number
    ---@param h number
    g.rect = function(x, y, w, h)
        _graffiti_native_context_rect(g.native_index, x, y, w, h)
        return g
    end

    ---@param x number
    ---@param y number
    ---@param w number
    ---@param h number
    ---@param r number
    ---@param r2 number|nil
    g.roundrect = function(x, y, w, h, r, r2)
        if r2 == nil then
            _graffiti_native_context_roundrect_1(g.native_index, x, y, w, h, r)
        else
            _graffiti_native_context_roundrect_2(g.native_index, x, y, w, h, r, r2)
        end
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    ---@param x2 number
    ---@param y2 number
    g.triangle = function(x0, y0, x1, y1, x2, y2)
        _graffiti_native_context_triangle(g.native_index, x0, y0, x1, y1, x2, y2)
        return g
    end

    ---@param cx number
    ---@param cy number
    ---@param rx number
    ---@param ry number
    ---@param start number
    ---@param sweep number
    g.arc = function(cx, cy, rx, ry, start, sweep)
        _graffiti_native_context_arc(g.native_index, cx, cy, rx, ry, start, sweep)
        return g
    end

    ---@param x number
    ---@param y number
    ---@param text string
    ---@param options table
    g.text = function(x, y, text, options)
        options = options or {}
        _graffiti_native_context_text(g.native_index, x, y, text, options.size or 50, options.font or "default.ttf")
        return g
    end

    ---@param cx number
    ---@param cy number
    ---@param rx number
    ---@param ry number
    ---@param start number
    ---@param sweep number
    g.arcto = function(cx, cy, rx, ry, start, sweep)
        _graffiti_native_context_arcTo(g.native_index, cx, cy, rx, ry, start, sweep)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    ---@param w number
    g.conicto = function(x0, y0, x1, y1, w)
        _graffiti_native_context_conicTo(g.native_index, x0, y0, x1, y1, w)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    ---@param x2 number
    ---@param y2 number
    g.cubicto = function(x0, y0, x1, y1, x2, y2)
        _graffiti_native_context_cubicTo(g.native_index, x0, y0, x1, y1, x2, y2)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    g.lineto = function(x0, y0)
        _graffiti_native_context_lineTo(g.native_index, x0, y0)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    g.moveto = function(x0, y0)
        _graffiti_native_context_moveTo(g.native_index, x0, y0)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    g.quadto = function(x0, y0, x1, y1)
        _graffiti_native_context_quadTo(g.native_index, x0, y0, x1, y1)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    g.arcquadrantto = function(x0, y0, x1, y1)
        _graffiti_native_context_arcQuadrantTo(g.native_index, x0, y0, x1, y1)
        return g
    end

    ---@param rx number
    ---@param ry number
    ---@param x1 number
    ---@param y1 number
    ---@param options table
    g.ellipticarcto = function(rx, ry, x1, y1, options)
        options = options or {}
        _graffiti_native_context_ellipticArcTo(g.native_index, rx, ry, options.rotation or 0, options.large or false,
            options.sweep or false, x1, y1)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    g.smoothcubicto = function(x0, y0, x1, y1)
        _graffiti_native_context_smoothCubicTo(g.native_index, x0, y0, x1, y1)
        return g
    end

    ---@param x0 number
    ---@param y0 number
    g.smoothquadto = function(x0, y0)
        _graffiti_native_context_smoothQuadTo(g.native_index, x0, y0)
        return g
    end

    g.closepath = function()
        _graffiti_native_context_closepath(g.native_index)
        return g
    end

    g.fill = function(...)
        local args = table.pack(...)
        if #args == 1 then
            return g._fillall(args[1])
        elseif #args == 5 then
            return g._fillrect(args[1], args[2], args[3], args[4], args[5])
        else
            asser("wrong number of args for fill")
        end
    end

    g._fillall = function(pattern)
        if (type(pattern) == "number") then
            _graffiti_native_context_fill_i32(g.native_index, pattern)
        elseif (type(pattern) == "table" and pattern.type == "gradient") then
            _graffiti_native_context_fill_gradient(g.native_index, pattern.native_index)
        elseif (type(pattern) == "table" and pattern.type == "context") then
            _graffiti_native_context_fill_context(g.native_index, pattern.native_index)
        end
        return g
    end

    g._fillrect = function(pattern, x, y, w, h)
        if (type(pattern) == "number") then
            _graffiti_native_context_fill_i32_rect(g.native_index, pattern, x, y, w, h)
        elseif (type(pattern) == "table" and pattern.type == "gradient") then
            _graffiti_native_context_fill_gradient_rect(g.native_index, pattern.native_index, x, y, w, h)
        elseif (type(pattern) == "table" and pattern.type == "context") then
            _graffiti_native_context_fill_context_rect(g.native_index, pattern.native_index, x, y, w, h)
        end
        return g
    end

    g.stroke = function(pattern, options)
        options = options or {}
        if (type(pattern) == "number") then
            _graffiti_native_context_stroke_i32(g.native_index, pattern, options.width or unit:pixel(1),
                options.startcap or cap.butt, options.endcap or cap.butt, options.join or join.miterclip)
        elseif (type(pattern) == "table" and pattern.type == "gradient") then
            _graffiti_native_context_stroke_gradient(g.native_index, pattern.native_index, options.width or unit:pixel(1),
                options.startcap or cap.butt, options.endcap or cap.butt, options.join or join.miterclip)
        elseif (type(pattern) == "table" and pattern.type == "context") then
            _graffiti_native_context_stroke_context(g.native_index, pattern.native_index, options.width or unit:pixel(1),
                options.startcap or cap.butt, options.endcap or cap.butt, options.join or join.miterclip)
        end
        return g
    end

    g.close = function()
        _graffiti_native_context_close()
        return g
    end
    --     
    -- 
    ---@param angle number
    ---@param cx number|nil
    ---@param cy number|nil
    g.rotate = function(angle, cx, cy)
        _graffiti_native_context_rotate(g.native_index, angle, cx or 50, cy or 50)
        return g
    end

    ---@param w number
    ---@param h number
    g.resize = function(w, h)
        _graffiti_native_context_resize(g.native_index, w / 100.0, h / 100.0)
        return g
    end

    ---@param x number
    ---@param y number
    g.translate = function(x, y)
        _graffiti_native_context_translate(g.native_index, x, y)
        return g
    end

    g.export = function(filename)
        _graffiti_native_context_export(g.native_index, filename)
        return g
    end
    return g
end

Graffiti = {
    _VERSION = "2023.1",
    layers = {},
    image = function(...)
        local args = table.pack(...)
        assert(#args == 2, "images can only be created with 2 args")
        return gc:new(args[1], args[2])
    end
}

function gg(index)
    return gc:new(_graffiti_native_get_width(), _graffiti_native_get_height(), _graffiti_native_gg(index))
end

function font(filename)
    assert(type(filename) == "string", "filename must to be a string")
    return _graffiti_native_font(filename)
end

function pad(str, size)
    size = size or 10
    for i = 1, size do
        str = str .. " "
    end
    return str
end

Gradient = {
    _resolveSteps = function(gradient, steps)
        assert(#steps % 2 == 0, #steps .. " steps are not allowed")
        local pair = {}
        for _, item in pairs(steps) do
            pair[#pair + 1] = item
            if #pair == 2 then
                pair[1] = pair[1] / 100.0
                _graffiti_native_gradient_step(gradient.native_index, pair[1], pair[2])
                pair = {}
            end
        end
        return gradient
    end,

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    linear = function(x0, y0, x1, y1)
        local gradient = {
            type = "gradient",
            native_index = _graffiti_native_new_linear_gradient(x0, y0, x1, y1)
        }
        return function(steps)
            return Gradient._resolveSteps(gradient, steps)
        end
    end,

    ---@param x0 number
    ---@param y0 number
    ---@param x1 number
    ---@param y1 number
    ---@param r0 number
    radial = function(x0, y0, x1, y1, r0)
        local gradient = {
            type = "gradient",
            native_index = _graffiti_native_new_radial_gradient(x0, y0, x1, y1, r0)
        }
        return function(steps)
            return Gradient._resolveSteps(gradient, steps)
        end
    end
}

gradient = Gradient

Graffiti.__index = Graffiti

g = Graffiti
