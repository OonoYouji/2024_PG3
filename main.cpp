#include <stdio.h>
#include <format>


/// <summary>
/// 給与計算関数:時給1072円
/// </summary>
/// <param name="time">		稼働時間(h)</param>
/// <param name="isDefault">通常の給与計算をするか</param>
/// <returns>給与</returns>
int Salary(int time, bool isDefault = true);

int DefaultSalary(int time);
int RecoverySalary(int time);


int main() {

	printf("/// 一般的な賃金体系と再起的な賃金体系を比較する\n");
	printf("--------------------------------------------------------------------------------\n");

	printf(std::format("	default  salary = {}円\n", Salary(5)).c_str());
	printf(std::format("	recovery salary = {}円\n", Salary(5, false)).c_str());

	printf("--------------------------------------------------------------------------------\n");
	printf("\n");



	printf("/// 何時間働くと、再帰的な賃金体系の方が儲かるか計算する\n");
	printf("--------------------------------------------------------------------------------\n");

	int count          = 0;
	int defaultSalary  = 0;
	int recoverySalary = 0;
	while(true) {
		count++;

		defaultSalary  += Salary(count);
		recoverySalary += Salary(count, false);
	
		if(recoverySalary > defaultSalary) {
			printf("/// 再帰的な賃金体系が一般的な賃金体系の給与を超えたので計算を終了する\n");

			printf(std::format("時間 : {}/h\n", count).c_str());
			printf(std::format("一般的な給与 : {}円\n", defaultSalary).c_str());
			printf(std::format("再帰的な給与 : {}円\n", recoverySalary).c_str());

			break;
		}
	}


	printf("--------------------------------------------------------------------------------\n");


	return 0;
}






int Salary(int time, bool isDefault) {
	if(isDefault) {
		return DefaultSalary(time);
	}

	return RecoverySalary(time);
}

int DefaultSalary(int time) {
	const int kOneTimeSalary = 1072;
	return kOneTimeSalary * time;
}

int RecoverySalary(int time) {
	if(time <= 1) {
		return 100;
	}
	return RecoverySalary(time - 1) * 2 - 50;
}
