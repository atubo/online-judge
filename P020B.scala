object P020B extends App {
  def solve(a: List[Long]): Tuple3[Int, Any, Any] = {
    val det = a(1)*a(1) - 4*a(0)*a(2)
    if (det < 0) return new Tuple3(0, Unit, Unit);
    val x1 = -0.5*a(1)/a(0)
    if (det == 0) return new Tuple3(1, x1, Unit);
    val x2 = 0.5*math.sqrt(det)/a(0)
    return new Tuple3(2, x1-x2, x1+x2)
  }
    
  var a = readLine.split(' ').map(_.toLong).toList
  if (a(0) < 0) a = a.map(-_)
  val result = a match {
    case List(0, 0, 0) => (-1, Unit, Unit)
    case 0::0::tail => (0, Unit, Unit)
    case 0::tail => (1, -1.0*a(2)/a(1), Unit)
    case _ => solve(a)
  }
  println(result._1)
  if (result._1 >= 1) printf("%.8f\n", result._2);
  if (result._1 >= 2) printf("%.8f\n", result._3);
}
