# Deep RL Project - Workspace

Ce projet est organisé en **Workspace** pour séparer les algorithmes d'apprentissage des environnements de simulation.

## Structure des Dossiers

### Bibliothèques (Cœur du projet)

* **`algo_lib/`** : Contient tous les algorithmes de DRL (PPO, MuZero, DQN...).
* **`env_lib/`** : Contient les environnements (GridWorld, TicTacToe...).
* **`src/`** : Le point d'entrée principal (`main.rs`) pour lancer des entraînements globaux.

### Tests, Démos & Perf

* **`examples/`** : Petits programmes de démonstration.
* *Usage :* `cargo run --example line_world`


* **`tests/`** : Tests d'intégration pour vérifier que les algos et les envs communiquent bien.
* *Usage :* `cargo test`


* **`benches/`** : Tests de performance (vitesse de calcul des algos).
* *Usage :* `cargo bench`



---

## Commandes Utiles

| Action | Commande |
| --- | --- |
| **Compiler tout** | `cargo build` |
| **Lancer le main** | `cargo run` |
| **Lancer un exemple** | `cargo run --example <nom>` |
| **Tester tout le projet** | `cargo test` |

---

## Dépendances

Les versions des bibliothèques externes (comme `ndarray`) sont centralisées dans le **Cargo.toml racine** pour garantir la cohérence entre `algo_lib` et `env_lib`.
