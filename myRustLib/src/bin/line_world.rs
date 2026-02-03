use env_lib::envs::line_world::LineWorld;
// use algo_lib::algos::alpha_zero;
fn main() {
    let mut lw: LineWorld = LineWorld::new();

    println!("{}", lw.state);
    lw.step(0);
    println!("{}", lw.state);
}

// cargo run --bin line_word_exp
