require_relative 'geom'

class Perlin
  def lerp(a, b, s)
    a + s * (b - a)
  end
  
  def value(x, y)
    x0 = x.floor.to_i
    x1 = x0 + 1
    y0 = y.floor.to_i
    y1 = y0 + 1

    sx = x - x0.to_f
    sy = y - y0.to_f

    n0 = dot(x0, y0, x, y)
    n1 = dot(x1, y0, x, y)
    ix0 = lerp(n0, n1, sx)
    n0 = dot(x0, y1, x, y)
    n1 = dot(x1, y1, x, y)
    ix1 = lerp(n0, n1, sx)

    value = lerp(ix0, ix1, sy)

    value * 0.5 + 0.5
  end

  def fbm(x, y, freq, oct)
    xa = x * freq.to_f
    ya = y * freq.to_f
    amp = 1.0
    final = 0
    div = 0.0

    oct.times {
      div += amp
      final += value(xa, ya) * amp
      amp *= 0.5
      xa *= 2
      ya *= 2
    }

    final / div
  end

  private

  def fade(t)
    t * t * t * (t * (t * 6 - 15) + 10)
  end

  def dot(ix, iy, x, y)
    angle = grad(ix, iy)

    dx = x - ix.to_f
    dy = y - iy.to_f

    dx * Math.cos(angle) + dy * Math.sin(angle)
  end

  def grad(x, y)
    w = 8 * 4
    s = w / 2
    max = 2 ** w

    a = x
    b = y

    a *= 3284157443
    b ^= a << s | a >> w-s
    b *= 1911520717
    a ^= b << s | b >> w-s
    a *= 2048419325

    a %= max

    a * (Math::PI * 2 / max)
  end
end
