//#pragma once
//#include "Core/Component.h"
//#include "Core/GameObject.h"
//#include "Components/SquareCollider.h"
//#include "PlayerJ.h" 
//
//namespace BulletHell_J {
//    class CollisionManagerJ : public Component {
//    public:
//        GameObject* playerRef = nullptr;
//        GameObject* enemyRef = nullptr;
//
//        void Update(const float _dt) override {
//            if (!playerRef || !enemyRef) return;
//
//            PlayerJ* pComp = playerRef->GetComponent<PlayerJ>();
//            SquareCollider* pCol = playerRef->GetComponent<SquareCollider>();
//            SquareCollider* eCol = enemyRef->GetComponent<SquareCollider>();
//
//            if (pComp && pCol && eCol) {
//                if (SquareCollider::IsColliding(*pCol, *eCol)) {
//                    pComp->TakeDamage();
//                }
//            }
//        }
//    };
//}