object P040A extends App {
  def sqrt(x: Int):Int = {
    var i = 0
    var j = 2000
    while (j > i + 1) {
      val mid = (i + j) / 2
      if (mid * mid > x) j = mid
      else               i = mid
    }
    return i;
  }
  def findQuadrant(x: Int, y: Int):Int = {
    return (if (x*y > 0) 0 else 1)
  }
  def solve(x: Int, y: Int):String = {
    if (x == 0 || y == 0) return "black"
    val r = sqrt(x*x + y*y)
    if (r*r == x*x + y*y) return "black"
    val quadrant= findQuadrant(x, y)
    if (r % 2 == quadrant % 2) return "black"
    else                       return "white"
  }

  val param = readLine().split(' ').map(_.toInt)
  println(solve(param(0), param(1)))
}
