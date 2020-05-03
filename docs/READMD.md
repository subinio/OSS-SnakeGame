# Contributor guide
추가나 수정하고 싶은 규칙이 있다면 [Issue 4](https://github.com/kimkyeongnam/OSS-SnakeGame/issues/4)를 통해 의견 교환
<br><br>

## 1. Commit 메세지
* 제목과 본문을 한 줄 띄워 분리하기
* 제목은 50자 이내로
* 제목 첫글자를 대문자로
* 제목 끝에 `.` 금지
* 제목은 `명령조`로
* 본문은 `어떻게`보다 `무엇을`, `왜`에 맞춰 작성하기
* 본문 작성 시 변경내용마다 번호를 붙여 작성하기
<br><br><br>

## 2. Branch 규칙
### ■/issNum_△ 기준으로

■: clean(코드 개선), bug(버그 수정), new(기능 추가)
△: 구체적인 키워드

**예)new/iss55_tail   -> 기능추가: issue55번에서 토론_꼬리 에 관한**
<br><br><br>

## 3. 변수 작성 방법
* 변수는 한 목적으로만 사용하기
* 변수는 항상 소문자로 시작하고, 다음 단어는 대문자로 구분하기 
* 함수의 매개변수 역시 그 의미를 명확히 표현하는 단어로 작성하기
<br><br><br>

## 4. 함수 작성 방법
* 함수명은 항상 대문자로 시작하고, 다음단어는 대문자로 구분하기
* 변수명과 함수명을 같게 하지 말기
* 함수의 접두사 공통으로 사용하기

![func](https://user-images.githubusercontent.com/38516906/57505454-5817ec80-7333-11e9-8ee8-c2a700097677.PNG)
<br><br><br>

## 5. 버전 표기 기준
![version](https://user-images.githubusercontent.com/38516906/57505348-f788af80-7332-11e9-9252-cad4557edd8a.PNG)

* x: 기존 버전과 호환되지 않게 바뀔 시(대규모 업데이트)
* y: 기존 버전과 호환되면서 새로운 기능을 추가할 때
```
InitMap(): 0
DrawMap(): 1
GetInput(): 2
EatFood(): 3
Die(): 4
main(): 5


추후 추가되는 함수는 순차적으로 번호 부여
 ㄴ> 추가한 번호는 해당 댓글을 edit하여 계속 추가 바람
```
* z: 기존 버전과 호환되면서 버그 수정했을 시
```
수정하지 않을 시: 0
수정할 시: 1
```
* 부가설명: 기여한 부분 설명

예) GetInput() 버그수정 및 새로운 기능(Enter를 누를 시 게임 일시정지) 추가.  기존 버전과 호환됨: **0.2.1-enter**
<br><br><br>

## 6. Merge 규칙
### 1) Merge 확인 작업
각자 맡은 코드 수정 후,<br>
팀원은 Pull request에 있는 해당 Issue를 보고 피드백을 남긴다.(merge 찬성 혹은 개선 내용 추가)
<br><br>

### 2) Merge 결정 후
Merge를 하기로 결정났으면 merge를 진행한다.
<br><br><br>

## 7. Issue 규칙
한 기능 당 하나의 issue 생성
<br><br><br>

## 8. Wiki 규칙
Issue와 관련된 정보 모으기
FAQ 생성
