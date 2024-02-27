<?php
class Terrain {
    // can this be seen by the player?
    private $visible;
    
    // how difficult is the terrain to pass
    private $cost;
    
    public function __construct() {
        $this->visible = false;
        $this->cost = rand(0, 9);
    }

    public function setVisible($v = null) {
        if (is_null($v)) {
            $this->visible = true;
        } else {
            $this->visible = $v;
        }
    }

    public function isVisible() {
        return $this->visible;
    }

    public function getCost() {
        return $this->cost;
    }
}