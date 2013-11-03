object P032A extends App {
  def upper(a: Array[Int], pos: Int, h: Int):Int = {
    var i = pos
    val b = a(i) + h
    var j = a.length - 1
    if (a(j) <= b) return j;
    while (j > i + 1) {
      val mid = (i + j) / 2
      if (a(mid) <= b) i = mid
      else             j = mid
    }
    return i
  }
  def lower(a: Array[Int], pos:Int, h: Int):Int = {
    var i = 0
    var j = pos
    val b = a(j) - h
    if (a(i) >= b) return i
    while (j > i + 1) {
      val mid = (i + j) / 2
      if (a(mid) < b) i = mid
      else            j = mid
    }
    return j;
  }

  val param = readLine.split(' ').map(_.toInt)
  val a = readLine.split(' ').map(_.toInt).sorted
  var result = 0
  for (i <- 0 to param(0)-1) {
    result += upper(a, i, param(1)) - lower(a, i, param(1))
  }
  print(result)
}
