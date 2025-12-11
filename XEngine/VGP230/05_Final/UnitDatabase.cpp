#include "UnitDatabase.h"
#include "Infantry.h"
// #include "Archer.h"
// #include "Ram.h"

Attacker* UnitDatabase::ReturnAttackerUnit(UnitEnum unit) // Consider changing to enum
{
    switch (unit)
    {
    case INFANTRY:
        return new Infantry();
    case ARCHER:
        // return std::make_unique<Archer>();
        break;
    case RAM:
        // return std::make_unique<Ram>();
        break;
    default:
        return new Attacker();
    }

    return new Attacker();
}


//internal class MonsterDatabase
//{
//    public static Monster Create(MonsterData name, Player player) // Consider changing to enum
//    {
//        return name switch // Personal note, this return switch is really cool
//        {
//            MonsterData.GoblinLooterA = > new GoblinLooter(player, true),
//                MonsterData.GoblinLooterB = > new GoblinLooter(player, false),
//                MonsterData.ShaleGolemA = > new ShaleGolem(player, true),
//                MonsterData.ShaleGolemB = > new ShaleGolem(player, false),
//                MonsterData.LargeLeechA = > new LargeLeech(player, true),
//                MonsterData.LargeLeechB = > new LargeLeech(player, false),
//                MonsterData.RecklessOgreA = > new RecklessOgre(player, true),
//                MonsterData.RecklessOgreB = > new RecklessOgre(player, false),
//                MonsterData.ClumsyOgreA = > new ClumsyOgre(player, true),
//                MonsterData.ClumsyOgreB = > new ClumsyOgre(player, false),
//                MonsterData.PebbleBeastA = > new PebbleBeast(player, true),
//                MonsterData.PebbleBeastB = > new PebbleBeast(player, false),
//                MonsterData.Boss = > new Boss(player),
//                _ = > new Monster(player, "Unknown", false, 10, 2, 0, 1) // No match, though shouldn't happen
//        };
//    }
//}
