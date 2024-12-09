#pragma once

class ScoreSystem {

private:
	int score;

public:
	ScoreSystem() : score(0) {}
	~ScoreSystem() = default;

	void addScore(int score) {
		this->score += score;
	}

	int getScore() {
		return this->score;
	}

};
