#[derive(Copy,Clone)]
pub enum Noise<'a> {
    Value,
    Perlin,
    Simplex,
    Fbm(&'a Noise<'a>, FbmParams),
}

#[derive(Copy, Clone)]
pub struct FbmParams {
    pub octaves: u32,
    pub frequency: f32,
    pub amplitude: f32,
    pub lacunarity: f32,
    pub persistence: f32,
}

pub const DEFAULT_FBM_PARAMS: FbmParams = FbmParams {
    octaves: 3,
    frequency: 1.0,
    amplitude: 1.0,
    lacunarity: 2.0,
    persistence: 0.5,
};

struct Vec2 {
    x: f32,
    y: f32,
}

impl Vec2 {
    fn dot(self, v: Vec2) -> f32 {
        self.x * v.x + self.y * v.y
    }
}

impl Noise<'_> {
    pub fn get2d(self, x: f32, y: f32) -> f32 {
        match self {
            Self::Value => Self::value2d(x, y),
            Self::Perlin => Self::perlin2d(x, y),
            Self::Simplex => Self::simplex2d(x, y),
            Self::Fbm(ns, ps) => Self::fbm2d(x, y, *ns, ps),
        }
    }

    pub fn lerp(a: f32, b: f32, t: f32) -> f32 {
        if t < 0.0 {
            a
        } else if t > 1.0 {
            b
        } else {
            (1.0 - t) * a + t * b
        }
    }

    pub fn smooth(t: f32) -> f32 {
        (3.0 - 2.0 * t) * t * t
    }

    pub fn smoother(t: f32) -> f32 {
        (t * (t * 6.0 - 15.0) + 1.0) * t * t * t
    }

    pub fn norm(v: f32, mn: f32, mx: f32) -> f32 {
        (v - mn) / (mx - mn)
    }

    pub fn hash2d(x: i32, y: i32) -> u32 {
        let w = 8 * u32::BITS as usize;
        let s = w / 2;

        let mut a = std::num::Wrapping(x as u32);
        let mut b = std::num::Wrapping(y as u32);

        a *= std::num::Wrapping(3_284_157_443u32); b ^= a << s | a >> (w - s);
        b *= std::num::Wrapping(1_911_520_717u32); a ^= b << s | b >> (w - s);
        a *= std::num::Wrapping(2_048_419_325u32);
        a.0
    }

    pub fn hash2df(x: i32, y: i32) -> f32 {
        (Self::hash2d(x, y) as f32) / (u32::MAX as f32)
    }

    fn grad2d(ix: i32, iy: i32) -> Vec2 {
        let angle = Self::hash2df(ix, iy) * std::f32::consts::TAU;
        Vec2 {
            x: angle.cos(),
            y: angle.sin(),
        }
    }

    fn value2d(x: f32, y: f32) -> f32 {
        let ix = x.floor() as i32;
        let iy = y.floor() as i32;
        let fx = x - (ix as f32);
        let fy = y - (iy as f32);
        let u = Self::smoother(fx);
        let v = Self::smoother(fy);

        let h1 = Self::hash2df(ix, iy);
        let h2 = Self::hash2df(ix+1, iy);
        let h3 = Self::hash2df(ix, iy+1);
        let h4 = Self::hash2df(ix+1, iy+1);

        Self::lerp(
            Self::lerp(h1, h2, u),
            Self::lerp(h3, h4, u),
            v) * 2.0 - 1.0
    }

    fn perlin2d(x: f32, y: f32) -> f32 {
        let ix = x.floor() as i32;
        let iy = y.floor() as i32;
        let fx = x - (ix as f32);
        let fy = y - (iy as f32);
        let u = Self::smoother(fx);
        let v = Self::smoother(fy);

        let g1 = Self::grad2d(ix, iy);
        let g2 = Self::grad2d(ix+1, iy);
        let g3 = Self::grad2d(ix, iy+1);
        let g4 = Self::grad2d(ix+1, iy+1);

        Self::lerp(
            Self::lerp(
                g1.dot(Vec2{ x: fx, y: fy}),
                g2.dot(Vec2{ x: fx-1.0, y: fy }),
                u),
            Self::lerp(
                g3.dot(Vec2{ x: fx, y: fy-1.0 }),
                g4.dot(Vec2{ x: fx-1.0, y:fy-1.0 }),
                u),
            v)
    }

    fn simplex2d(x: f32, y: f32) -> f32 {
        let F2 = 0.5 * (3.0_f32.sqrt() - 1.0);
        let s = (x + y) * F2;
        let i = (x + s).floor() as i32;
        let j = (y + s).floor() as i32;
        let G2 = (3.0 - 3.0_f32.sqrt()) / 6.0;
        let t = ((i + j) as f32) * G2;
        let X0 = (i as f32) - t;
        let Y0 = (j as f32) - t;
        let x0 = x - X0;
        let y0 = y - Y0;

        let (i1, j1) = if x0 > y0 {
            (1, 0)
        } else {
            (0, 1)
        };

        let x1 = x0 - (i1 as f32) + G2;
        let y1 = y0 - (j1 as f32) + G2;
        let x2 = x0 - 1.0 + 2.0 * G2;
        let y2 = y0 - 1.0 + 2.0 * G2;

        let gi0 = Vec2 {
            x: i as f32,
            y: j as f32,
        };
        let gi1 = Vec2 {
            x: (i+i1) as f32,
            y: (j+j1) as f32,
        };
        let gi2 = Vec2 {
            x: (i+1) as f32,
            y: (j+1) as f32,
        };

        let t0 = 0.5 - x0 * x0 - y0 * y0;
        let n0 = if t0 < 0.0 {
            0.0
        } else {
            let t0 = t0 * t0;
            t0 * t0 * gi0.dot(Vec2{ x: x0, y: y0 })
        };
        let t1 = 0.5 - x1 * x1 - y1 * y1;
        let n1 = if t1 < 0.0 {
            0.0
        } else {
            let t1 = t1 * t1;
            t1 * t1 * gi1.dot(Vec2{ x: x1, y: y1 })
        };
        let t2 = 0.5 - x2 * x2 - y2 * y2;
        let n2 = if t2 < 0.0 {
            0.0
        } else {
            let t2 = t2 * t2;
            t2 * t2 * gi2.dot(Vec2{ x: x2, y: y2 })
        };

        70.0 * (n0 + n1 + n2)
    }

    fn fbm2d(x: f32, y: f32, ns: Noise, ps: FbmParams) -> f32 {
        let mut xa = x * ps.frequency;
        let mut ya = y * ps.frequency;
        let mut amp = ps.amplitude;
        let mut res: f32 = 0.0;
        let mut div: f32 = 0.0;
        for _ in 0..ps.octaves {
            res += ns.get2d(xa, ya) * amp;
            div += amp;
            xa *= ps.lacunarity;
            ya *= ps.lacunarity;
            amp *= ps.persistence;
        }
        res / div
    }
}
