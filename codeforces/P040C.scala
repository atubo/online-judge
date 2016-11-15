import math.max
import math.min
object P040C extends App {
  val param = readLine().split(' ').map(_.toInt)
  var l = param(3) - param(1)
  var n = param(0)
  var m = param(2)
  if (l < 0) {
    l = -l
    n = param(2)
    m = param(0)
  }

  var nr: Long = 0
  for (i <- 1 to n) {
    if (i <= l) {
      val nc = max(0, min(m, l+i-1) - (l-i+1) + 1)
      nr += max(2 * nc - 1, 0)
    }
    else {
      val nc = max(0, min(m, l+i-1) - (i-l) + 1);
      nr += max(2 * (nc -1), 0)
    }
  }
  print(n + m + 1 + nr)
}
    
