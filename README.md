# HW08 플랫폼 게임

- 회전, 이동하는 플랫폼과 장애물을 피해 모든 🍬을 모아 종료 지점까지 도달하는 게임
- [HW06](https://github.com/SKim041/HW06)에서 발전시킨 게임이다.
## 📜게임 규칙
- 플레이어의 목숨은 3개 ❤️❤️❤️
- 플레이어가 떨어져 목숨을 잃게 되면 이전 위치에서 리스폰된다.
- 해당 레벨의 모든 사탕을 모으지 못하면 종료 지점에 도달해도 레벨을 끝낼 수 없다.

## 🎬플레이 영상
 [![YouTube](https://img.youtube.com/vi/EjW6DnwgEJ0/0.jpg)](https://www.youtube.com/watch?v=EjW6DnwgEJ0)
## 📌추가 구현 기능
**1. 레벨별 랜덤 스폰되는 아이템**
 - 💊힐링 포션: 먹으면 목숨 +1, 최대 목숨에 도달하면 더이상 채워지지 않는다.
 - 😫섬광탄: 닿으면 2초동안 시야가 하얘진다.
 - 🎯유도탄: 범위 안에 들어가면 그 위치로 3초동안 따라온다. 그 안에 맞으면 터지며 목숨을 하나 잃고 범위에서 벗어나면 사라진다.
   
**2. 레벨별 스폰 맵 모듈 추가**

 - 레벨별로 맵이 스폰될 그리드가 커지며 스폰되는 맵 모듈도 둘 중 하나가 무작위로 선택된다.  
![MapModule](https://github.com/user-attachments/assets/a0aabc52-b0a6-4fcd-8f25-8d111d230c49)

**3. 추가 레벨**
 - 3 레벨까지  추가
 - Level 1: 사탕 모으기 + 힐링 포션
 - Level 2: 사탕 모으기 + 힐링 포션 + 섬광탄
 - Level 3: 사탕 모으기 + 힐링 포션 + 섬광탄 + 유도탄
   
**4. 리스폰 로직 수정**
 - 2초마다 이동/회전 플랫폼이 아닌곳에 서있는 경우 리스폰 지점 갱신
   
**5. UI**
 - 메인 메뉴에 Quit 버튼 추가
 - 레벨 사이 시작 화면 추가
 - HUD 추가
   
**6. 사운드** 
 - 아이템 사운드
 - 레벨 별 배경음악
 - 걷는 소리

## 💀사용 에셋
맵: 
[Cropout Smaple Project](https://www.fab.com/ko/listings/bd733d81-7c29-44fe-b53f-65b14d06a9e2)

캐릭터: [Cemetery - Mummy - Undead Character | Free Gift December 2024](https://www.fab.com/ko/listings/b2a3ddd5-2933-4313-8131-c5e03b24fff9)

사탕 아이템: [Cute Candy](https://www.fab.com/ko/listings/f48a3022-06ee-4788-9f63-76a3850583aa)

장애물, 플랫폼: 내일배움캠프 언리얼 3/4기 제공

배경 음악
- 배달은 자신있어 by 배달의 민족 
- 미래도시라솔파 by 배달의 민족 
- 거의 다 왔어요 by 배달의 민족 
