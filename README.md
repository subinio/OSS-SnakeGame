<div align="center">
  <h1 align="center">Snake Game</h1>
  <p align="center">
    세종대학교 2019년 1학기 오픈소스SW개론(002) 팀프로젝트  
    <br><b>Original Project</b>: <a href=https://github.com/abdulwahid2802/SnakeGame> abdulwahid2802/SnakeGame </a>
  </p>
  <p align="center">
    이 Repository는 세종대학교 오픈소스SW개론 과목에서 Github를 통한 오픈소스 기여 텀 프로젝트를 수행하기 위해<br>
    Snake Game을 주제로 설정 및 개선하기 위해 만들어졌습니다.<br>
기존 코드에서 클린코드, UI 개선, 버그 수정에 초점을 두고 프로젝트를 진행하였습니다.<br>
자세한 사항은 <a href=https://github.com/kimkyeongnam/OSS-SnakeGame/wiki> Wiki </a>를 참고해주시길 바랍니다.<br>
  </p>
</div>


<br><br>


## Table of contents
* Directory/File Structure Diagram
* SW Changes
* Execution environment
* Execution screen
* How to execute
* How to play
* How to contribute
* License
* FAQ
* Contributer's Infomation

<br><br><br>

## 1. Directory/File Structure Diagram
```
main.c
```
<br>

## 2. SW Changes
* Snake 구조를 double linked list로 구현
* Intro 생성
* 점수에 따른 속도 설정
* Food를 먹을 시 snake의 꼬리 생성
* Map, 점수, 생명, 스피드를 출력하는 UI 위치 변경

<br>

## 3. Execution environment  
Windows 10에서 C언어 기반의 콘솔응용프로그램(Visual Studio 2017)을 통해 개발 (C버전: 99)

<br>

## 4. Execution screen
### 게임 초기 화면
![intro](https://user-images.githubusercontent.com/38516906/58689640-846ada00-83c2-11e9-8e59-0a1366d41475.PNG)

### 게임 실행 화면
![running](https://user-images.githubusercontent.com/38516906/58689674-a4020280-83c2-11e9-9dfb-4c2bba9fe02c.png)


<br>

## 5. How to execute
    1. Project Fork
    2. Git Bash 프로그램 실행 후 저장소 clone

<br>

## 6. How to play
* 키보드 방향키(↑, ↓, ←, →)를 이용해 snake(모양: Oo)를 움직인다.<br>
* Snake의 머리가 벽에 부딪히거나 / snake의 몸에 부딪히면 생명(Lives)이 감소한다.<br>
* Food(모양: FF)를 먹을 시 snake의 꼬리가 생성된다<br>
* Food를 먹어 일정조건을 만족하면 snake의 speed가 빨라진다.

<br>

## 7. How to contribute
    1. Project Fork
    2. git bash 프로그램 실행 후 저장소 clone
    3. .git 파일 생성 확인 후 main.c 파일 수정
    4. remote 저장소로 pull request 요청

<br>

## 8. License
[Open-source under MIT license](https://tldrlegal.com/license/mit-license)


<br>

## 9. FAQ
FAQ는 [Issue #38](https://github.com/kimkyeongnam/OSS-SnakeGame/issues/38)을 통해 운영되고 있습니다.

<br>

## 10. Contributors
|Name|Github|Email|
|:--:|:--:|:--:|
|김경남|[@kimkyeongnam](https://github.com/kimkyeongnam)|kkyy0126@naver.com|
|진수빈|[@subinio](https://github.com/subinio)|subinjin22@gmail.com|

