/*!
 * \class CDiscAdjMultizoneDriver.hpp
 * \brief Class for driving adjoint multi-zone problems.
 * \author O. Burghardt, T. Albring, R. Sanchez
 * \version 6.2.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "CMultizoneDriver.hpp"

class CDiscAdjMultizoneDriver : public CMultizoneDriver {

protected:

  /*!
   * \brief Kinds of recordings (three different ones).
   */
  enum ENUM_TAPE {
    FULL_TAPE = 1,                /*!< \brief Entire derivative information for a coupled adjoint
                                              solution update. */
    OBJECTIVE_FUNCTION_TAPE = 2,  /*!< \brief Record only the dependence of the objective function
                                              w.r.t. solver variables (from all zones). */
    ZONE_SPECIFIC_TAPE = 3        /*!< \brief Record only the dependence of the solution update in a
                                              specified zone w.r.t. solver variables (from all zones). */
  };

  /*!
   * \brief Position markers within a tape.
   */
  enum ENUM_TAPE_POSITIONS {
    START = 0,                    /*!< \brief Beginning of the tape. */
    REGISTERED = 1,               /*!< \brief Solver variables are registered on the tape. */
    DEPENDENCIES = 2,             /*!< \brief Derived values (e.g. gradients) are set. */
    OBJECTIVE_FUNCTION = 3,       /*!< \brief Objective function is set. */
    TRANSFER = 4,                 /*!< \brief Solution data is transferred between coupled solvers of
                                              different physical zones (giving cross contributions). */
    ITERATION_READY = 5           /*!< \brief Until here, all derivative information is gathered so
                                              that it can be connected to a solver update evaluation. */
  };

  unsigned short RecordingState;  /*!< \brief The kind of recording that the tape currently holds. */
  bool retape;                    /*!< \brief Boolean whether a full tape can be kept in memory. */

  su2double ObjFunc;              /*!< \brief Value of the objective function. */
  int ObjFunc_Index;              /*!< \brief Index of the value of the objective function. */

  CIteration*** direct_iteration; /*!< \brief Array of pointers to the direct iterations. */
  COutput** direct_output;        /*!< \brief Array of pointers to the direct outputs. */
  unsigned short* direct_nInst;   /*!< \brief Total number of instances in the direct problem. */
  unsigned short* nInnerIter;     /*!< \brief Number of inner iterations for each zone. */


public:

  /*!
   * \brief Constructor of the class.
   * \param[in] confFile - Configuration file name.
   * \param[in] val_nZone - Total number of zones.
   * \param[in] MPICommunicator - MPI communicator for SU2.
   */
  CDiscAdjMultizoneDriver(char* confFile,
             unsigned short val_nZone,
             SU2_Comm MPICommunicator);

  /*!
   * \brief Destructor of the class.
   */
  ~CDiscAdjMultizoneDriver(void);

  /*!
   * \brief [Overload] Launch the computation for discrete adjoint multizone problems.
   */
  void StartSolver();

  /*!
   * \brief Run an discrete adjoint update of all solvers within multiple zones.
   */
  void Run();

//  /*!
//   * \brief Check the convergence at the outer level.
//   */
//  bool OuterConvergence(unsigned long OuterIter);

  /*!
   * \brief Record one iteration of a flow iteration in within multiple zones.
   * \param[in] kind_recording - Type of recording (either FLOW_CONS_VARS, MESH_COORDS, COMBINED or NONE)
   * \param[in] indicator which part of a solution update will be recorded
   * \param[in] record_zone - zone where solution update will be recorded
   */
  void SetRecording(unsigned short kind_recording, unsigned short tape_type, unsigned short record_zone);

  /*!
   * \brief Run one direct iteration in a zone.
   */
  void DirectIteration(unsigned short iZone, unsigned short kind_recording);

  /*!
   * \brief Set the objective function. It is virtual because it depends on the kind of physics.
   */
  void SetObjFunction(unsigned short kind_recording);

  /*!
   * \brief Initialize the adjoint value of the objective function.
   */
  void SetAdj_ObjFunction();

  /*!
   * \brief Summary of all routines to evaluate the adjoints in iZone.
   * \param[in] iZone - Zone in which adjoints are evaluated depending on their (preceding) seeding.
   */
  void ComputeAdjoints(unsigned short iZone);

  /*!
   * \brief Add External_Old vector to Solution.
   * \param[in] iZone - Zone where data between solvers is transferred.
   */
  void AddSolution_ExternalOld(unsigned short iZone);

  /*!
   * \brief Saves the current (adjoint) Solution vector to Solution_BGS_k.
   * \param[in] iZone - Zone where data between solvers is transferred.
   */
  void Set_BGSSolution(unsigned short iZone);

  /*!
   * \brief Sets External to zero.
   */
  void SetExternal_Zero(void);

  /*!
   * \brief Add Solution vector to External.
   * \param[in] iZone - Zone where data between solvers is transferred.
   */
  void AddExternal_Solution(unsigned short iZone);

  /*!
   * \brief Add Solution vector to External_Old.
   * \param[in] iZone - Zone where data between solvers is transferred.
   */
  void AddExternalOld_Solution(unsigned short iZone);

  /*!
   * \brief Set the current solution (adjoint) values to the current iterated ones.
   */
  void Set_OldExternal(void);

  /*!
   * \brief Compute BGS residuals.
   * \param[in] iZone - Zone where solver residuals are computed.
   */
  void SetResidual_BGS(unsigned short iZone);
};
