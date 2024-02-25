<?php
class Path {
    public $terrain;
    public $origTown;
    public $destTown;
    public $yPos;

    public function __construct($orig = false, $dest = false) {
        $this->terrain = array();

        // add random terrain
        for ($x = 0; $x < 5; $x++) {
            $this->terrain[] = new Terrain\Plains();
        }

        $this->yPos = 0;
    }

    public function getDistance() {
        return count($this->terrain);
    }

    public function setDestTown($d) {
        $this->destTown = $d;
    }

    public function getDestTown() {
        return $this->destTown;
    }

    public function getOrigTown() {
        return $this->origTown;
    }

    public function getTerrain($y) {
        // return the terrain at position $y
        if (isset($this->terrain[$y])) {
            return $this->terrain[$y];
        }

        return false;
    }

    private function terrainToString() {
        if ($this->yPos == 0) {
            $ret = Colors::bg_color("light_gray", "X");
        } else {
            $ret = "X";
        }
        
        $ret .= "-";

        foreach ($this->terrain as $count => $t) {
            if ($count == $this->yPos - 1) {
                $ret .= "[" . Colors::bg_color("light_gray", $t) . "]-";
            } else {
                $ret .= "[$t]-";
            }
        }

        if (count($this->terrain) + 1 == $this->yPos) {
            $ret .= Colors::bg_color("light_gray", "X");
        } else {
            $ret .= "X";
        }

        return $ret;
    }

    public function reversePath() {
        $this->terrain = array_reverse($this->terrain);
        $tmp = $this->orig;
        $this->orig = $this->dest;
        $this->dest = $tmp;
    }

    public function __toString() {
        $ret = "PATH: ";

        $ret .= $this->terrainToString() . " ";
        $ret .= "yPos: " . $this->yPos . "\n";
        
        return $ret;
    }
}