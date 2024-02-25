<?php
namespace Terrain;

class Plains {
    public $cost;

    public function __construct() {
        $this->cost = rand(0, 10);
    }

    public function getCost() {
        return $this->cost;
    }

    public function __toString() {
        return "P" . $this->cost;
    }
}