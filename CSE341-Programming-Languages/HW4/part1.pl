room(z06,50,[projector,smartboard,none]).

room(z10,60,[projector,smartboard,none]).

room(z23,80,[projector,smartboard,handicapped,none]).

room(z04,10,[none]).

room(z11,40,[projector,smartboard,none]).



course(cse102,yakup_genc,[8,9],60,z23,[]).

course(cse341,yakup_genc,[11-12],50,z23,[]).

course(cse241,ysa,[8,9,10,11],50,z10,[]).

course(cse331,alparslan_bayrakci,[13,14,15],70,z23,[]).

course(cse321,didem_gozupek,[10,11],50,z10,[]).

course(cse343,habil_kalkan,[13,14],55,z11,[]).

course(cse101,habil_kalkan,[17,18],10,z4,[]).



instructor(yakup_genc,[cse102,cse341],[projector]).
instructor(ysa,[cse241],[projector]).
instructor(didem_gozupek,[cse321],[]).
instructor(alparslan_bayrakci,[cse331],[projector,smartboard]).
instructor(habil_kalkan,[cse101,cse343],[projector]).



student(ali,[cse241,cse341],handicapped).

student(mehmet,[cse102],none).

student(hasmet,[cse321,cse341,cse331],none).

student(sadri,[cse341],none).

student(ayhan,[cse241,cse331],none).






subset([], _).
subset([H|T], L) :- member(H, L), subset(T, L).


conflict(C1,C2):-
    course(C1,_,Hours1,_,Room1,_),
    course(C2,_,Hours2,_,Room2,_),
    (Room1 = Room2) ,nl,
    format('Courses Room is same ~w',[Room1]),
    nl,
    ((subset(Hours1,Hours2));
    (subset(Hours2, Hours1))),
    format('There is a conflict between ~w (Hours : ~w ) and ~w (Hours : ~w ). Course Hourses overlap.',[C1, Hours1,C2,Hours2]).



/*
assign(Course,Room):-
    course(Course,_,_,Cap,Room1,_),
    room(Room1,Cap1,Equipment),
    Cap =< Cap1,
    instructor(Course,_,Need),
    Equipment == need,
    format('Room ~w can be assigned to ~w',[Room, Course]).
*/

enroll(Student, Course):-
    course(Course,_,_,Cap,Room,Students),
    room(Room,_,Equipment),
    length(Students,Count),
    ((Count +1) =<  Cap),
    student(Student, Lectures, Handicapped),
    member(Handicapped,Equipment),
    member(Course,Lectures),
    format('~w can be enrolled to ~w',[Student, Course]).


assignment(Room,Course) :-
    room(Room,Cap,Equipment),
    course(Course,Instructor,Hours,CourseCap,RoomId,_),
    instructor(Id,Courses,Needs),
    member(Course,Courses),
    subset(Needs,Equipment),
    CourseCap =< Cap,
    RoomId = Room,
    
    (format('~w can be assign to ~w ',[Room, Course])).

addStudent(Id,Courses,Handicap) :- assertz(student(Id,Courses,Handicap)).
addCourse(Id,Lecturer,Hours,Capacity,Room) :- assertz(addCourse(Id,Lecturer,Hours,Capacity,Room,_)).
addRoom(Id,Capacity,Equipment) :- assertz(addRoom(Id,Capacity,Equipment)).




%conflict(cse241,cse341).


