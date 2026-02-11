use rand::Rng;
use env_lib::envs::monte_carlo_env::MonteCarloEnv;
pub fn deep_q_learning(
    mut env: impl MonteCarloEnv,
    episodes_count: usize,
    learning_rate: f32,
    rng: &mut impl Rng,
) -> (Vec<usize>, Vec<Vec<f32>>) {


    (vec![], vec![])
}