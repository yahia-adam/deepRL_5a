use crate::envs::monte_carlo_env::MonteCarloEnv ;

pub struct GridWorldEnv {
    pub agent_pos: usize
}

impl MonteCarloEnv for GridWorldEnv {
    fn state(&self) -> usize {
        self.agent_pos
    }

    fn num_states(&self) -> usize {
        todo!()
    }

    fn num_actions(&self) -> usize {
        todo!()
    }

    fn step(&mut self, a: usize) {
        todo!()
    }

    fn score(&self) -> f32 {
        todo!()
    }

    fn is_game_over(&self) -> bool {
        todo!()
    }

    fn reset(&mut self) {
        todo!()
    }
}