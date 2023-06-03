/**
 * INTEGR QUAD .m
  Sa = [a];
  Sb = [b];
  I = 0;

  while size(Sa,2) > 0 && size(Sb,2) > 0
    a = Sa(size(Sa,2));
    b = Sb(size(Sb,2));

    Sa = Sa(1:size(Sa,2)-1);
    Sb = Sb(1:size(Sb,2)-1);
    I1 = ((b - a)/2) * (f(a) + f(b));

    m = (a + b)/2;
    I2 = ((b - a)/4) * (f(a) + 2 * f(m) + f(b));

    if abs(I1 - I2) < 3 * (b - a) * TOL || (b - a) < TOL
      I = I2 + I;
    else
      Sa = [Sa, a];
      Sb = [Sb, m];

      Sa = [Sa, m];
      Sb = [Sb, b];
    endif
  endwhile
*/