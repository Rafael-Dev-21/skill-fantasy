mod noise;

use crossterm::{
    cursor::{Hide, MoveTo, Show},
    event::{self, Event, KeyCode, KeyEventKind, KeyModifiers},
    execute,
    style::{Color, Print, SetForegroundColor},
    terminal::{disable_raw_mode, enable_raw_mode, Clear, ClearType},
    ExecutableCommand, QueueableCommand,
};
use noise::{
    Noise::{Fbm, Simplex, Value, Perlin},
    DEFAULT_FBM_PARAMS,
};
use rayon::prelude::*;
use std::{
    io::{stdout, Stdout, Write},
    thread, time,
};

enum Action {
    Quit,
    Move(i16, i16),
}

fn handle_ev(ev: Event) -> Option<Action> {
    if let Event::Key(key) = ev {
        if key.kind == KeyEventKind::Press {
            if key.code == KeyCode::Char('q') && key.modifiers.contains(KeyModifiers::CONTROL) {
                Some(Action::Quit)
            } else {
                match key.code {
                    KeyCode::Char('k') => Some(Action::Move(0, -1)),
                    KeyCode::Char('j') => Some(Action::Move(0, 1)),
                    KeyCode::Char('h') => Some(Action::Move(-1, 0)),
                    KeyCode::Char('l') => Some(Action::Move(1, 0)),
                    _ => None
                }
            }
        } else {
            None
        }
    } else {
        None
    }
}

struct Player {
    x: u16,
    y: u16,
}

#[derive(Clone, Copy)]
enum Tile {
    Grass,
    Water,
    Sand,
    Mountain,
}

#[derive(Clone)]
struct World {
    width: usize,
    height: usize,
    tiles: Vec<Tile>,
}

impl World {
    fn generate(width: usize, height: usize) -> Self {
        let mut ps = DEFAULT_FBM_PARAMS;
        ps.octaves = 10;
        ps.amplitude = 64.0;
        let ns = Fbm(&Simplex, ps);
        let tiles: Vec<Tile> =
            (0..(width*height))
            .into_par_iter()
            .map(|idx| {
                let x = idx % width;
                let y = idx / width;
                let nx = x as f32 / 64.0 - 0.5;
                let ny = y as f32 / 32.0 - 0.5;
                let e = (ns.get2d(nx, ny) + 1.0) * 0.5;
                let e = (e * 1.5).powf(1.3);
                if e < 0.45 {
                    Tile::Water
                } else if e < 0.5 {
                    Tile::Sand
                } else if e < 0.8 {
                    Tile::Grass
                } else {
                    Tile::Mountain
                }
            })
            .collect();
        Self { width, height, tiles }
    }

    fn render(self, stdout: &mut Stdout, cam_x: u16, cam_y: u16) -> std::io::Result<()> {
        let commands: Vec<(u16, u16, Color, char)> = (0..(45*20))
            .into_par_iter()
            .map(|idx| {
                let x = idx % 45;
                let y = idx / 45;
                let x = x as u16;
                let y = y as u16;
                let idx =  (cam_x + x) as usize + (cam_y + y) as usize * self.width;
                let (color, ch) = match self.tiles[idx] {
                    Tile::Water => (Color::Blue, '7'),
                    Tile::Sand => (Color::Yellow, '~'),
                    Tile::Grass => (Color::Green, ','),
                    Tile::Mountain => (Color::White, '^'),
                };
                (x, y, color, ch)
            })
            .collect();
        for (x, y, color, ch) in commands.iter() {
            stdout.queue(MoveTo(*x, *y))?;
            stdout.queue(SetForegroundColor(*color))?;
            stdout.queue(Print(*ch))?;
        }
        Ok(())
    }
}

fn main() -> std::io::Result<()> {
    let mut stdout = stdout();
    enable_raw_mode()?;
    stdout.execute(Hide)?;
    stdout.execute(Clear(ClearType::All))?;

    let mut p = Player {
        x: 512,
        y: 512,
    };

    let mut w = World::generate(1024, 1024);

    'game: loop {
        stdout.queue(MoveTo(0, 0))?;
        stdout.queue(Clear(ClearType::All))?;
        w.clone().render(&mut stdout, p.x - 22, p.y - 10)?;
        stdout.queue(MoveTo(22, 10))?;
        stdout.queue(SetForegroundColor(Color::Red))?;
        stdout.queue(Print('@'))?;
        stdout.flush()?;

        if let Some(act) = handle_ev(event::read()?) {
            match act {
                Action::Quit => break 'game,
                Action::Move(dx, dy) => {
                    p.x = (p.x as i16 + dx) as u16;
                    p.y = (p.y as i16 + dy) as u16;
                },
            }
        }

        thread::sleep(time::Duration::from_millis(15));
    }

    disable_raw_mode()?;
    stdout.execute(Show)?;
    stdout.execute(MoveTo(0,0))?;
    stdout.execute(Clear(ClearType::All))?;
    Ok(())
}
