#ifndef SHOOTINGRANGE_H
#define SHOOTINGRANGE_H

#include "StaticTarget.h"

class ShootingRange
{
	private:
		Target** targets;
		int targetCount;

	public:
		ShootingRange() {
			targetCount = rand() % 5 + 3; // Случайное количество мишеней от 3 до 7
			targets = new Target*[targetCount];
			for (int i = 0; i < targetCount; i++)
			{
				double dist = (rand() % 100) + 10; // Расстояние от 10 до 110 метров
				double size = (rand() % 5) + 1; // Размер мишени от 1 до 5 м²
				int max_hits = (rand() % 5) + 1; // Количество попаданий, после которых мишень разрушается
				targets[i] = new StaticTarget(dist, size, max_hits);
			}
		}
		
		~ShootingRange() {
			for (int i = 0; i < targetCount; i++)
				delete targets[i];

			delete[] targets;
		}

		void simulate(Weapon& weapon)
		{
			std::cout << "Тестирование: " << weapon.name << "\n";
			weapon.displayCharacteristics();

			for (int i = 0; i < targetCount; i++)
			{
				Target* target = targets[i];
				if (!target->availability()) continue;

				double distance = target->get_size();
				int hits = 0;

				// Симуляция стрельбы
				for (int j = 0; j < 100; ++j)
				{
					int mode = rand() % 2 + 1; // Случайный выбор режима: 1 (одиночный) или 2 (очередь)
					weapon.fire(distance, mode, hits);
				}

				target->take_damage(hits);
				std::cout << *dynamic_cast<StaticTarget*>(target) << "\n"; // Вывод информации о мишени
			}
		}
};

#endif
