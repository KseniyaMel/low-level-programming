%define last 0

%macro colomn 2
%2:
	dq last
	db %1, 0
%define last %2
%endmacro
