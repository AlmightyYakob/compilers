program boo( input, output );
 var m,n: integer;
 function gcd(a,b: integer):integer;
 begin
     write(a);
     write(b);
     gcd := 1
 end;
begin
 read(m);
 read(n);
 m := gcd(m,n);
 write(m)
end.

