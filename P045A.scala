object P045A extends App {
  val month = List("January", "February", "March", "April", "May", "June",
                   "July", "August", "September", "October", "November",
                   "December")
  val monName = collection.mutable.Map[Int, String]();
  val monNum  = collection.mutable.Map[String, Int]();
  for (i <- 0 to 11) {
    monName(i) = month(i)
    monNum(month(i)) = i
  }
  val curMon = readLine
  val monLeft = readInt
  println(monName((monNum(curMon) + monLeft) % 12))
}

