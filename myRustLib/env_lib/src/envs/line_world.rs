use crate::envs::monte_carlo_env::MonteCarloEnv;

pub struct LineWorldEnv {
    pub agent_pos: usize
}

impl MonteCarloEnv for LineWorldEnv {
    fn state(&self) -> usize {
        self.agent_pos
    }

    fn num_states(&self) -> usize {
        5
    }

    fn num_actions(&self) -> usize {
        2
    }

    fn step(&mut self, a: usize) {
        assert!(!self.is_game_over());
        assert!(a < self.num_actions());

        match a {
            0 => self.agent_pos -= 1,
            1 => self.agent_pos += 1,
            _ => unreachable!()
        }
    }

    fn score(&self) -> f32 {
        match self.agent_pos {
            0 => -1f32,
            4 => 1f32,
            1..=3 => 0f32,
            _ => panic!("Invalid agent pos")
        }
    }

    fn is_game_over(&self) -> bool {
        self.agent_pos == 0 || self.agent_pos == 4
    }

    fn reset(&mut self) {
        self.agent_pos = 2;
    }
}