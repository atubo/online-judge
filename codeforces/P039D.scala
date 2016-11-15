object P039D extends App {
  val a = readLine.split(' ').map(_.toInt)
  val b = readLine.split(' ').map(_.toInt)
  val result = a.zip(b).map(x => x._1 ^ x._2).fold(1)(_ & _)
  println((if (result == 0) "YES" else  "NO"))
}
