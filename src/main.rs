use crossterm::{
    cursor::{Hide, MoveTo, Show},
    event::{self, Event, KeyCode, KeyEventKind, KeyModifiers},
    execute,
    style::{Color, Print, SetForegroundColor},
    terminal::{disable_raw_mode, enable_raw_mode, Clear, ClearType},
    ExecutableCommand, QueueableCommand,
};
use std::io::{stdout, Write};

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

fn main() -> std::io::Result<()> {
    let mut stdout = stdout();
    enable_raw_mode()?;
    stdout.execute(Hide)?;
    stdout.execute(Clear(ClearType::All))?;

    let mut p = Player {
        x: 10,
        y: 5,
    };

    'game: loop {
        stdout.queue(MoveTo(0, 0))?;
        stdout.queue(Clear(ClearType::All))?;
        stdout.queue(MoveTo(p.x, p.y))?;
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
    }

    disable_raw_mode()?;
    stdout.execute(Show)?;
    stdout.execute(MoveTo(0,0))?;
    stdout.execute(Clear(ClearType::All))?;
    Ok(())
}
