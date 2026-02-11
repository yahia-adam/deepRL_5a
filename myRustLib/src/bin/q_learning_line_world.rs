use rand::SeedableRng;
use rand_xoshiro::Xoshiro256PlusPlus;
use env_lib::envs::line_world::LineWorldEnv;
use algo_lib::algos::q_learning::q_learning;
fn main() {
    let env = LineWorldEnv {
        agent_pos: 2
    };

    let (pi, q) = q_learning(
        env,
        1_000_000,
        1f32,
        0.9999f32,
        0.1f32,
        &mut Xoshiro256PlusPlus::from_os_rng()
    );

    dbg!(pi);
    dbg!(q);
}