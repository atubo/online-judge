object P032C extends App {
  val a = readLine.split(' ').map(_.toLong)
  val f = (n: Long, s: Long) => ((n-1)%s+1) * ((n-1)/s+1)
  println(f(a(0), a(2)) * f(a(1), a(2)))
}
