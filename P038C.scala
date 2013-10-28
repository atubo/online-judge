object P038C extends App {
  val param = readLine.split(' ').map(_.toInt)
  val a = readLine.split(' ').map(_.toInt)
  val sol = new collection.mutable.ArrayBuffer[Int]()
  val maxLen = a.max
  for (i <- param(1) to maxLen) {
    sol += a.map(_/i).fold(0)(_+_) * i
  }
  println(if (sol.size == 0) 0 else sol max)
}
