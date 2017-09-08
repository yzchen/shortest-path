package shortestPath

class Node (val name: String, var neighbors: List[(String, Int)] = List(),
            var distance: Int = Int.MaxValue, var previous: String = "",
            var mask: Boolean = false) {

    override def toString: String = "[" + "name = " + name + ", neighbors = " + getNeighborsName(neighbors) +
                                          ", distance = " + distance + ", previous = " + previous +
                                          ", mask =" + mask + "]"

    private def getNeighborsName(nodeToInts: List[(String, Int)]):String = {
        var result: String = "List("

        for (neighbor <- nodeToInts) {
            result += "(name: " + neighbor._1 + " weight: " + neighbor._2 + ")"
        }

        result + ")"

    }
}

