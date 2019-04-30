program boo( input, output );
 var m,n: integer;
 procedure foo(a: integer);
 begin
	if (a = 1) then
		m := 1
	else
		m := a*2
 end;
begin
 read(n);
 foo(n);
 write(m)
end.

