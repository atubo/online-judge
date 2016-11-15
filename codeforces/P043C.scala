object P043C extends App {
  val n = readInt
  val a = readLine.split(' ').map(_.toInt)
  val r0 = a.count(_%3 == 0)
  val r1 = a.count(_%3 == 1)
  val r2 = a.count(_%3 == 2)
  println(r0/2 + math.min(r1, r2))
}
