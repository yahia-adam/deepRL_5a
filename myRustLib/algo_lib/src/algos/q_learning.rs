use rand::Rng;
use env_lib::envs::monte_carlo_env::MonteCarloEnv;
pub fn q_learning(
    mut env: impl MonteCarloEnv,
    episodes_count: usize,
    epsilon: f32,
    gamma: f32,
    alpha: f32,
    rng: &mut impl Rng,
) -> (Vec<usize>, Vec<Vec<f32>>) {
    let mut q = (0..env.num_states())
        .map(|_s|
            (0..env.num_actions())
                .map(|_a| rng.random_range(-1f32..1f32))
                .collect::<Vec<_>>()
        ).collect::<Vec<_>>();

    for _ep_id in 0..episodes_count {
        env.reset();
        let mut s = env.state();

        while !env.is_game_over() {
            let a = if rng.random_range(0f32..1f32) <= epsilon {
                rng.random_range(0..env.num_actions())
            } else {
                let mut best_a = 0;
                let mut best_a_score = f32::MIN;

                for a in 0..env.num_actions() {
                    if best_a_score <= q[s][a] {
                        best_a = a;
                        best_a_score = q[s][a];
                    }
                }

                best_a
            };

            let prev_score = env.score();
            env.step(a);
            let r = env.score() - prev_score;

            let s_p = env.state();
            if env.is_game_over() {
                for q_s_p_a in &mut q[s_p] {
                    *q_s_p_a = 0f32;
                }
            }

            [5, 6, 8, 1, 2, 3].iter().max();

            q[s][a] = q[s][a] +
                alpha * (r + gamma * q[s_p].iter().max_by(|a, b| a.partial_cmp(b).unwrap()).unwrap() - q[s][a]);

            s = s_p;
        }
    }

    let pi = q.iter()
        .map(|q_s| {
            let mut best_a = 0;
            let mut best_a_score = f32::MIN;

            for (a, &q_s_a) in q_s.iter().enumerate().take(env.num_actions()) {
                if best_a_score <= q_s_a {
                    best_a = a;
                    best_a_score = q_s_a;
                }
            }

            best_a
        }).collect::<Vec<_>>();

    (pi, q)
}