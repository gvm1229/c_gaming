#include <iostream>

class Monster {
private:
	std::string name;		// 몬스터 이름
	int hp;					// 생명력
	int origin_hp;			// 생명력 (불변값)
	int attack;				// 공격력
	int defense;			// 방어력
	std::string element;	// 속성: "불", "물", "땅", "바람"

	static int monster_count; // 몬스터의 총 개수 (정적 멤버 변수)

	static std::string generate_default_name() {
		char suffix = 'A' + monster_count++; // 몬스터 개수에 따라 A, B, C... 순서대로 이름 생성
		return "몬스터" + std::string(1, suffix);
	}

public:
	// 생성자
	Monster(std::string _name = "", int _hp = 1, int _attack = 1, int _defense = 0, std::string _element = "불")
		: name(_name), hp(_hp), attack(_attack), defense(_defense), element(_element) {
		if (hp < 1) hp = 1; // HP는 최소 1 이상 (즉시 종료 방지)
		origin_hp = hp; // 원래 생명력 저장 (불변값)

		if (_name.empty()) name = generate_default_name(); // 이름이 비어있으면 기본 이름으로 설정
		if (_attack < 1) attack = 1; // 공격력은 1 이상 (무한루프 방지, 종료조건은 몬스터 하나만 생존이기 때문에 서로 데미지를 줘야 함)
		if (_defense < 0) defense = 0; // 방어력은 0 을 최소값으로 유지, 음수 방어력은 의미가 없음
		if (_element != "불" && _element != "물" && _element != "땅" && _element != "바람") {
			element = "불"; // 기본 속성은 불로 설정, 이상한 속성 입력 방지
		}
	}

	// Getter
	// 몬스터 이름 반환
	std::string get_name() const {
		return name;
	}
	// 몬스터 HP 반환
	int get_hp() const {
		return hp;
	}
	// 몬스터 원래 HP 반환 (불변값)
	int get_origin_hp() const {
		return origin_hp;
	}
	// 몬스터 공격력 반환
	int get_attack() const {
		return attack;
	}
	// 몬스터 방어력 반환
	int get_defense() const {
		return defense;
	}
	// 몬스터 속성 반환
	std::string get_element() const {
		return element;
	}

	// 몬스터 정보 한눈에 출력
	void to_string() const {
		std::cout << "\"" << get_name() << "\", \t HP: " << get_hp() << "/" << get_origin_hp() << ", \t 공격력: " << get_attack() << ", \t 방어력: " << get_defense() << ", \t 속성: " << get_element() << std::endl;
	}

	// 데미지 받기
	void receive_damage(int damage) {
		hp -= damage;
		if (hp < 0) hp = 0; // HP는 0 을 최소값으로 유지, 음수 HP는 의미가 없기에 비허용

		std::cout << "몬스터 \"" << name << "\"이(가) [" << damage << "] 의 데미지를 받음. 현재 HP: " << hp << "/" << origin_hp << std::endl;

		if (hp == 0) { // HP가 0이 되면 몬스터 사망
			std::cout << "몬스터 \"" << name << "\"이(가) 사망." << std::endl;
		}
	}

	// 다른 몬스터에 공격
	void attack_monster(Monster& target) const {
		if (target.defense > attack) {
			std::cout << "몬스터 \"" << name << "\"이(가) 몬스터 \"" << target.name << "\"에 공격. 상대 방어력이 너무 높아 노데미지.\n\n";
			// 방어력이 공격력보다 크면 데미지는 0, 그러므로 공격하지 않고 함수 종료
			return;
		}

		int damage = attack - target.defense;

		std::cout << "몬스터 \"" << name << "\"이(가) 몬스터 \"" << target.name << "\"에 [" << damage << "] 만큼 공격. ";

		// static_cast를 통해 소수점 버림 처리
		if (
			(element == "불" && target.element == "바람") ||
			(element == "물" && target.element == "불") ||
			(element == "땅" && target.element == "불") ||
			(element == "바람" && target.element == "물") ||
			(element == "바람" && target.element == "땅")
			) {
			std::cout << "효과가 굉장했다! 데미지 1.5배!";
			damage = static_cast<int>(damage * 1.5); // 상성
		}
		else if (
			(element == "불" && target.element == "물") ||
			(element == "불" && target.element == "땅") ||
			(element == "물" && target.element == "바람") ||
			(element == "땅" && target.element == "바람") ||
			(element == "바람" && target.element == "불")
		) {
			std::cout << "효과가 별로였다.. 데미지 0.5배..";
			damage = static_cast<int>(damage * 0.5); // 역상성
		}

		std::cout << std::endl; // 줄 바꿈
		target.receive_damage(damage); // 타겟 몬스터에게 데미지 적용
		std::cout << std::endl; // 줄 바꿈
	}
};

class Arena {
private:
	Monster monsters[10];	// 최대 10마리 몬스터 (기본 A~J)
	int add_index = 0;		// 몬스터 추가를 위한 인덱스

public:
	// 몬스터 수용 제한 반환
	int get_arena_capacity() const {
		return sizeof(monsters) / sizeof(*monsters); // 몬스터 배열의 크기 반환
	}

	// 몬스터 추가
	void add_monster(const Monster& monster) {
		if (add_index >= get_arena_capacity()) {
			std::cout << "아레나가 몬스터가 가득 차 더 이상 추가할 수 없음." << std::endl;
			return; // 몬스터가 가득 찼으면 추가하지 않고 함수 종료
		}

		monsters[add_index++] = monster; // 몬스터 추가와 동시에 인덱스 증가
	}

	// 생명력이 가장 높은 몬스터 출력
	void print_healthiest_monster() const {
		std::cout << "가장 HP가 높은 몬스터: ";

		// 배열에 몬스터가 하나도 없을 경우
		if (add_index == 0) {
			std::cout << "아레나에 몬스터가 없음.";
			return; // 몬스터가 없으면 함수 종료
		}

		int max_hp = -1;
		int healthiest_index = -1;

		// 몬스터 배열을 순회하여 가장 높은 HP를 가진 몬스터 찾기
		// 순회는 add_index (다음 추가할 인덱스) 까지 진행, 즉 현재 추가된 몬스터들만 확인
		for (int i = 0; i < add_index; i++) {
			if (monsters[i].get_hp() >= max_hp) { // > 가 아니라 >= 로 설정하여 동률인 경우 뒤에 있는 몬스터를 선택
				max_hp = monsters[i].get_hp();
				healthiest_index = i;
			}
		}

		if (healthiest_index != -1) {
			std::cout << "몬스터 \"" << monsters[healthiest_index].get_name() << "\", HP: " << monsters[healthiest_index].get_hp() << "/" << monsters[healthiest_index].get_origin_hp();
		} else {
			std::cout << "아레나에 몬스터가 없음."; // 만약 healthiest_index 가 -1 인 경우, 몬스터가 없다는 의미
		}

		std::cout << "\n\n"; // 간격 유지
	}

	// 아레나의 현재 몬스터 수 출력
	void print_current_monster_count() const {
		std::cout << "현재 아레나에 있는 몬스터 수: " << add_index << std::endl;
		std::cout << std::endl; // 간격 유지
	}

	// 아레나의 몬스터 목록 출력
	void print_monster_list() const {
		std::cout << "[아레나에 있는 몬스터 목록]" << std::endl;

		if (add_index == 0) {
			std::cout << "- 아레나에 몬스터가 없음." << std::endl;
			return; // 몬스터가 없으면 함수 종료
		}

		for (int i = 0; i < add_index; i++) {
			std::cout << "- 몬스터 " << (i + 1) << " ";
			monsters[i].to_string();
		}

		std::cout << std::endl; // 간격 유지
	}

	// 우승 몬스터 출력
	void print_winner() const {
		if (add_index >= 2) {
			std::cout << "아직 경기 진행 중. 아레나에 아직 몬스터가 2마리 이상 남아있음." << std::endl;
			return; // 몬스터가 2마리 이상이면 아직 경기 진행 중아가 때문에 우승자를 출력하지 않고 함수 종료
		}
		if (add_index == 0) {
			std::cout << "아레나에 몬스터가 없음. 우승자가 없음." << std::endl;
			return; // 몬스터가 없으면 우승자도 없음, 그럼 함수 종료
		}

		for (int i = 0; i < add_index; i++) {
			if (monsters[i].get_hp() > 0) { // 살아있는 몬스터만 출력
				std::cout << "우승 몬스터: \"" << monsters[i].get_name() << "\", HP: " << monsters[i].get_hp() << "/" << monsters[i].get_origin_hp() << std::endl;
				return; // 첫번째 살아있는 몬스터를 우승자로 출력 후 함수 종료
			}
		}

		std::cout << "모든 몬스터가 사망하여 우승자가 없음." << std::endl; // 모든 몬스터가 사망한 경우
	}

	// 경기 함수
	void go_to_round() {
		if (add_index < 2) {
			std::cout << "경기를 진행할 몬스터가 부족. 최소 2마리 이상 필요." << std::endl;
			return; // 몬스터가 2마리 미만이면 우승자가 답정너거나 없기 때문에 경기를 진행하지 않음
		}

		while (add_index > 1) { // 몬스터가 2마리 이상일 때만 경기 진행
			int turn = 1; // 턴 초기화
			for (int i = 0; i < add_index; i++) {
				if (monsters[i].get_hp() > 0) { // 살아있는 몬스터만 공격
					std::cout << "[" << turn++ << "턴]" << std::endl;
					monsters[i].attack_monster(monsters[(i + 1) % add_index]); // 다음 몬스터 공격, 마지막 몬스터는 첫번째 몬스터 공격
				}
			}

			// 살아남은 몬스터 수 업데이트
			int new_index = 0;
			for (int i = 0; i < add_index; i++) {
				if (monsters[i].get_hp() > 0) {
					monsters[new_index++] = monsters[i]; // 살아있는 몬스터를 앞으로 이동
				}
			}

			add_index = new_index; // 새로운 인덱스 업데이트

			std::cout << "\n\n"; // 간격 유지
			print_current_monster_count(); // 현재 몬스터 수 출력
			print_monster_list(); // 현재 몬스터 목록 출력
			print_healthiest_monster(); // 가장 HP가 높은 몬스터 출력
			std::cout << "\n\n"; // 간격 유지
		}
	}
};

// 정적 멤버 변수 초기화
int Monster::monster_count = 0; // 몬스터 개수 초기화

int main() {
	// 아레나 생성
	Arena arena;

	// 몬스터 추가
	// Monster monsters[10] 코드로 인해 이 이후 익명 몬스터는 "몬스터K" 부터 시작됨
	// vector 를 사용하면 "몬스터A" 부터 시작 가능하지만 현재 배열 제한으로는 이러함
	arena.add_monster(Monster("불의 드래곤", 100, 20, 10, "불"));
	arena.add_monster(Monster("", 30, 5, 0, "바람")); // 1번째 사용자 익명 몬스터, "몬스터K" 라고 명명되어야 함
	arena.add_monster(Monster("물의 마법사", 90, 15, 8, "물"));
	arena.add_monster(Monster("땅의 트롤", 70, 10, 5, "땅"));
	arena.add_monster(Monster("불의 정령", 60, 12, 3, "불"));
	arena.add_monster(Monster("", 50, 6, 5, "바람")); // 2번째 사용자 익명 몬스터, "몬스터L" 라고 명명되어야 함
	arena.add_monster(Monster("물의 정령", 80, 15, 5, "물"));
	arena.add_monster(Monster("바람의 요정", 60, 10, 3, "바람"));
	arena.add_monster(Monster("땅의 거인", 120, 25, 15, "땅"));
	//arena.add_monster(Monster("있어선 안될 치트", 9999, 9999, 9999, "불"));

	// 현재 몬스터 수 출력
	arena.print_current_monster_count();
	// 현재 몬스터 목록 출력
	arena.print_monster_list();
	// 가장 HP가 높은 몬스터 출력
	arena.print_healthiest_monster();
	// 경기 진행
	arena.go_to_round();
	// 우승자 출력
	arena.print_winner();

	return 0;
}