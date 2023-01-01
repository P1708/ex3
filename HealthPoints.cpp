//
// Created by ahmad.fadool on 12/21/22.
//
#include "HealthPoints.h"


HealthPoints::HealthPoints(int maxHp)
{
    if(maxHp<=0)
    {
        throw InvalidArgument();
    }
    this->hp=maxHp;
    this->maxHp=maxHp;

}

HealthPoints operator+(int change , const HealthPoints& healthPoint)
{
    if(change<0)
    {
        return healthPoint - (-1*change);
    }
    HealthPoints tmpHp;
    tmpHp.maxHp=healthPoint.maxHp;
    if(healthPoint.hp+change>=healthPoint.maxHp)
    {
        tmpHp.hp=tmpHp.maxHp;
        return tmpHp;

    }
    else
    {
        tmpHp.hp=healthPoint.hp+change;
        return tmpHp;
    }

}

HealthPoints HealthPoints::operator-(int change) const
{
    if(change<0)
    {
        return (*this + (-1* change));
    }
    HealthPoints tmpHp;
    tmpHp.maxHp=this->maxHp;
    if(this->hp-change<=ZERO_HP)
    {
        tmpHp.hp=ZERO_HP;
        return tmpHp;

    }
    else
    {
        tmpHp.hp=this->hp-change;
        return tmpHp;
    }
}

HealthPoints HealthPoints::operator+(int change) const
{
    return (change + *this);
}


std::ostream& operator<<(std::ostream& os , const HealthPoints& healthPoint)
{
    return os<<healthPoint.hp<<'('<<healthPoint.maxHp<<')';
}

HealthPoints& HealthPoints::operator+=(int change)
{
    (*this) =change+(*this);
    return (*this);
}

HealthPoints &HealthPoints::operator-=(int change)
{
    (*this)=(*this)-change;
    return (*this);
}

bool HealthPoints::operator==(const HealthPoints &healthPoint) const
{
    return (this->hp==healthPoint.hp);
}

bool HealthPoints::operator==(int hp) const
{
    return (this->hp==hp);
}

bool operator==(int hp,const HealthPoints& healthPoint)
{
    return healthPoint==hp;
}

bool HealthPoints::operator!=(const HealthPoints &healthPoint) const
{
    return !(healthPoint == (*this));
}

bool HealthPoints::operator!=(int hp) const
{
    return !(hp==(*this));
}

bool operator!=(int hp,const HealthPoints& healthPoint)
{
    return healthPoint!=hp;
}

bool HealthPoints::operator<(const HealthPoints &healthPoint) const
{
    return (this->hp < healthPoint.hp);
}

bool HealthPoints::operator>(const HealthPoints &healthPoint) const
{
    return (this->hp > healthPoint.hp);
}

bool HealthPoints::operator<=(const HealthPoints &healthPoint) const
{
    return !((*this)>healthPoint);
}

bool HealthPoints::operator>=(const HealthPoints &healthPoint) const
{
    return !((*this)<healthPoint);
}

