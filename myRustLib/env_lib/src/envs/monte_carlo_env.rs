pub trait MonteCarloEnv {
    fn state(&self) -> usize;
    fn num_states(&self) -> usize;
    fn num_actions(&self) -> usize;
    fn step(&mut self, a: usize);
    fn score(&self) -> f32;
    fn is_game_over(&self) -> bool;
    fn reset(&mut self);
}
