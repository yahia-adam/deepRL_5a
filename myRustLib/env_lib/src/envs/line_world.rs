use ndarray::Array4;

pub struct LineWorld {
    pub states: Vec<u32>,
    pub actions: Vec<u32>,
    pub rewards: Vec<f32>,
    pub terminal_states: Vec<u32>,

    pub initial_state: u32,
    pub state: u32,
    pub inner_score: f32,

    pub p_matrix: Array4<f32>,
}

impl LineWorld {
    pub fn new() -> Self {
        let states = vec![0, 1, 2, 3, 4];
        let actions = vec![0, 1];  // 0: gauche, 1: droite
        let rewards = vec![-1.0, 0.0, 1.0];
        let terminal_states = vec![0, 4];
        let initial_state = 2;

        let mut p_matrix = Array4::zeros((
            states.len(), actions.len(), states.len(), rewards.len()
        ));

        // state init, action, next state, expected reward == prob
        p_matrix[[3, 0, 2, 1]] = 1.0;
        p_matrix[[2, 0, 1, 1]] = 1.0;
        p_matrix[[1, 0, 0, 0]] = 1.0;
        p_matrix[[1, 1, 2, 1]] = 1.0;
        p_matrix[[2, 1, 3, 1]] = 1.0;
        p_matrix[[3, 1, 4, 2]] = 1.0;

        LineWorld {
            states,
            actions,
            rewards,
            terminal_states,
            initial_state,
            state: initial_state,
            inner_score: 0.0,
            p_matrix,
        }
    }

    pub fn is_forbidden(&self, action: u32) -> bool {
        if self.terminal_states.contains(&self.state) {
            return true;
        }
        if action == 0 && self.state == 0 {
            return true;
        }
        if action == 1 && self.state == 4 {
            return true;
        }
        false
    }

    pub fn step(&mut self, action: u32) {
        if self.terminal_states.contains(&self.state) {
            panic!("L'épisode est terminé.");
        }

        if self.is_forbidden(action) {
            return;
        }

        if action == 0 {
            self.state -= 1;
        } else if action == 1 {
            self.state += 1;
        }

        if self.state == 0 {
            self.inner_score = self.rewards[0];
        } else if self.state == 4 {
            self.inner_score = self.rewards[2];
        } else {
            self.inner_score = self.rewards[1];
        }
    }
}
