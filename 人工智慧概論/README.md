# 人工智慧概論：Pacman 強化學習

> 課程專案（project-6-rl）：以 Q-Learning 與 Deep Q-Learning 訓練 Pacman 代理人。

## 簡介

本專案以課程提供的強化學習框架為基礎（Gridworld、Crawler、Pacman 環境與自動評分程式），補完 `qlearningAgents.py` 中的 Q-Learning 程式碼，使代理人能在 Gridworld 與 Pacman 中學習；另外包含 Deep Q-Learning 版本的 Pacman 代理人。

## 完成部分

- `qlearningAgents.py`：補完 Q 值計算、依 Q 值選擇動作、ε-greedy 探索與 Q 值更新
- 其餘檔案（遊戲環境、圖形介面、自動評分、測試案例）為課程提供的框架

## 技術

Python、強化學習（Q-Learning、Approximate Q-Learning、Deep Q-Learning）

## 執行方式

```bash
python autograder.py                      # 執行所有測試
python gridworld.py -a q -k 5 -m          # 手動操作 Gridworld 觀察 Q-Learning
python pacman.py -p PacmanQAgent -x 2000 -n 2010 -l smallGrid   # 訓練 2000 局後測試 10 局
```
