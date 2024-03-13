[ButtonBase]

-Property
    MoveTime : 버튼이 움직이는데(들어가거나 나오는데) 걸리는 시간    
    MoveOffset : 버튼이 어디까지 움직일지 설정해주는 Offset
    bButtonInteract(수정불가) : 현재 버튼과 상호작용중인지 체크한다

-Function
    MoveButton
        플레이어가 버튼과 상호작용중일때 버튼을 움직인다
    ButtonBeginOverlap - virtual
        버튼과 상호작용 시작시 이벤트
    ButtonEndOverlap - virtual
        버튼 상호작용 끝날시 이벤트


[PressButton] : [ButtonBase]

-Function
    ButtonBeginOverlap
        대상이 Character라면 bButtonInteract = true
    ButtonEndOverlap
        대상이 Character라면 bButtonInteract = false


[SlideButton] : [ButtonBase]

-Property
    InteractWidget (Type : Hold)
        상호작용 가능함 알려주는 Widget

-Function
    ButtonBeginOverlap
        대상이 Character라면 InteractWidget Active (Type : Hold)
    ButtonEndOverlap
        대상이 Character라면 InteractWidget Disactive (Type : Hold)
