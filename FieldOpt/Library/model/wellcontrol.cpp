/*
 * This file is part of the FieldOpt project.
 *
 * Copyright (C) 2015-2015 Einar J.M. Baumann <einarjba@stud.ntnu.no>
 *
 * The code is largely based on ResOpt, created by  Aleksander O. Juell <aleksander.juell@ntnu.no>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#include "wellcontrol.h"

WellControl::WellControl(const WellControl &c)
{
    m_type = c.m_type;
    m_end_time = c.m_end_time;
    setControlVar(shared_ptr<RealVariable>(new RealVariable(*c.p_control_var)));
}

QString WellControl::description()
{
    QString str(" " + QString::number(endTime()) + " " +
                QString::number(p_control_var->value()) + " " +
                QString::number(p_control_var->max()) + " " +
                QString::number(p_control_var->min()) + " ");

    if(type() == BHP) str.append("BHP");
    else if(type() == QGAS) str.append("GAS");
    else if(type() == QOIL) str.append("OIL");
    else if(type() == QWAT) str.append("WAT");

    str.append("\n");

    return str;
}