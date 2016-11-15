object P034A extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  val next = (x: Int) => (x+1) % n
  val b = for (i <- 0 to n-1) yield math.abs(a(i)-a(next(i)))
  val pos = b.indexOf(b min)
  printf("%d %d\n", pos+1, next(pos)+1)
}

