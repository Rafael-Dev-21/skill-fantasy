struct Player {
    x: i32,
    y: i32,
}

fn main() {
    let width = 40;
    let height = 25;

    let p = Player {
        x: width / 2,
        y: height / 2,
    };

    for y in -1..=height {
        for x in -1..=width {
            if x == -1 && y == -1 {
                print!("+");
            } else if x == width && y == -1 {
                print!("+");
            } else if x == -1 && y == height {
                print!("+");
            } else if x == width && y == height {
                print!("+");
            } else if x == -1 || x == width {
                print!("|");
            } else if y == -1 || y == height {
                print!("—");
            } else if x == p.x && y == p.y {
                print!("@");
            } else {
                print!(".");
            }
        }
        print!("\n");
    }
}
