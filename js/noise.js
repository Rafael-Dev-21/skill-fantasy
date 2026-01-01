let seed = 0x1234567;

function rng32() {
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

function hsh32(x, y) {
  let result = 0x1234567;
  result = result * 631 + x;
  result = result * 631 + y;
  result ^= result << 13;
  result ^= result >> 17;
  result ^= result << 5;
  return result;
}

function val8(x, y) {
  let ix = Math.floor(x);
  let iy = Math.floor(y);
  let fx = x - ix;
  let fy = y - iy;
  let u = smoothQuintic(fx);
  let v = smoothQuintic(fy);
  let h00 = hsh32(ix, iy)&255;
  let h10 = hsh32(ix+1, iy)&255;
  let h01 = hsh32(ix, iy+1)&255;
  let h11 = hsh32(ix+1, iy+1)&255;
  return lerp(lerp(h00, h10, u), lerp(h01, h11, u), v);
}

function val8o(x, y) {
  let xa = x;
  let ya = y;
  let a = 1.0;
  let div = 0;
  let fin = 0;
  for (let o = 0; o < 3; o++) {
    fin += (val8(xa, ya)*2-255) * a;
    div += a;
    xa *= 2;
    ya *= 2;
    a *= 0.58;
  }
  fin = fin * 0.5 + 0.5;
  return Math.floor(fin / div);
}

function hsh3d32(x, y, z) {
  let result = 0x1234567;
  result = result * 631 + x;
  result = result * 631 + y;
  result = result * 631 + z;
  result ^= result << 13;
  result ^= result >> 17;
  result ^= result << 5;
  return result;
}

function val3d8(x, y, z) {
  let ix = Math.floor(x);
  let iy = Math.floor(y);
  let iz = Math.floor(z);
  let fx = x - ix;
  let fy = y - iy;
  let fz = z - iz;
  let u = smoothQuintic(fx);
  let v = smoothQuintic(fy);
  let r = smoothQuintic(fz);
  let h000 = hsh3d32(ix, iy, iz)&255;
  let h100 = hsh3d32(ix+1, iy, iz)&255;
  let h010 = hsh3d32(ix, iy+1, iz)&255;
  let h110 = hsh3d32(ix+1, iy+1, iz)&255;
  let h001 = hsh3d32(ix, iy, iz+1)&255;
  let h101 = hsh3d32(ix+1, iy, iz+1)&255;
  let h011 = hsh3d32(ix, iy+1, iz+1)&255;
  let h111 = hsh3d32(ix+1, iy+1, iz+1)&255;
  return lerp(
    lerp(
      lerp(h000, h100, u),
      lerp(h010, h110, u),
      v),
    lerp(
      lerp(h001, h101, u),
      lerp(h011, h111, u),
      v),
    r);
}

function val3d8o(x, y, z) {
  let xa = x;
  let ya = y;
  let za = z;
  let a = 1.0;
  let div = 0;
  let fin = 0;
  for (let o = 0; o < 3; o++) {
    fin += (val3d8(xa, ya, za)*2-255) * a;
    div += a;
    xa *= 2;
    ya *= 2;
    za *= 2;
    a *= 0.58;
  }
  fin = fin * 0.5 + 0.5;
  return Math.floor(fin / div);
}

rng32(); rng32();
