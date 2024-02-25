<?php
class Town {
    public $name;
    public $restCost;
    public $level;

    public function __construct($level = null) {
        $this->name = uniqid("TOWN-", true);
        $this->restCost = rand(0, 10);

        if (!$level) {
            $this->level = 1;
        } else {
            $this->level = $level;
        }
    }

    public function getName() {
        return $this->name;
    }

    public function getRestCost() {
        return $this->restCost;
    }

    public function __toString() {
        $ret = "TOWN Name: " . $this->getName() . " ";
        $ret .= "Rest Cost: " . $this->getRestCost() . "\n";

        return $ret;
    }
}