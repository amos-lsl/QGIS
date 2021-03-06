/***************************************************************************
                         qgsprocessingmodelchildalgorithm.h
                         ----------------------------------
    begin                : June 2017
    copyright            : (C) 2017 by Nyall Dawson
    email                : nyall dot dawson at gmail dot com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef QGSPROCESSINGMODELCHILDALGORITHM_H
#define QGSPROCESSINGMODELCHILDALGORITHM_H

#include "qgis_core.h"
#include "qgis.h"
#include "qgsprocessingmodelcomponent.h"
#include "qgsprocessingmodelchildparametersource.h"
#include "qgsprocessingmodeloutput.h"
#include <memory>

class QgsProcessingModelAlgorithm;
class QgsProcessingAlgorithm;

///@cond NOT_STABLE

/**
 * Child algorithm representing a single component of a QgsProcessingModelAlgorithm.
 * \ingroup core
 * \since QGIS 3.0
 */
class CORE_EXPORT QgsProcessingModelChildAlgorithm : public QgsProcessingModelComponent
{
  public:

    /**
     * Constructor for QgsProcessingModelChildAlgorithm. The \a algorithmId parameter
     * should be set to a QgsProcessingAlgorithm algorithm ID.
     */
    QgsProcessingModelChildAlgorithm( const QString &algorithmId = QString() );

    QgsProcessingModelChildAlgorithm( const QgsProcessingModelChildAlgorithm &other );
    QgsProcessingModelChildAlgorithm &operator=( const QgsProcessingModelChildAlgorithm &other );

    /**
     * Returns the child algorithm's unique ID string, used the identify
     * this child algorithm within its parent model.
     * \see setChildId()
     * \see generateChildId()
     */
    QString childId() const { return mId; }

    /**
     * Sets the child algorithm's unique \a id string, used the identify
     * this child algorithm within its parent model.
     * \see childId()
     * \see generateChildId()
     */
    void setChildId( const QString &id ) { mId = id; }

    /**
     * Automatically generates a unique childId() for the algorithm,
     * avoiding child IDs which are already present in \a model.
     * \see childId()
     * \see setChildId()
     */
    void generateChildId( const QgsProcessingModelAlgorithm &model );

    /**
     * Returns the underlying child algorithm's ID.
     * \see algorithm()
     * \see setAlgorithmId()
     */
    QString algorithmId() const { return mAlgorithmId; }

    /**
     * Sets the underlying child algorithm's ID. This
     * should be set to an existing QgsProcessingAlgorithm algorithm ID.
     * \see algorithm()
     * \see algorithmId()
     */
    void setAlgorithmId( const QString &algorithmId );

    /**
     * Returns the child algorithm's configuration map.
     *
     * This map specifies configuration settings which are passed
     * to the algorithm, allowing it to dynamically adjust its initialized parameters
     * and outputs according to this configuration. This allows child algorithms in the model
     * to adjust their behavior at run time according to some user configuration.
     *
     * \see setConfiguration()
     */
    QVariantMap configuration() const;

    /**
     * Sets the child algorithm's \a configuration map.
     *
     * This map specifies configuration settings which are passed
     * to the algorithm, allowing it to dynamically adjust its initialized parameters
     * and outputs according to this configuration. This allows child algorithms in the model
     * to adjust their behavior at run time according to some user configuration.
     *
     * \see configuration()
     */
    void setConfiguration( const QVariantMap &configuration );

    /**
     * Returns the underlying child algorithm, or a nullptr
     * if a matching algorithm is not available.
     * \see algorithmId()
     */
    const QgsProcessingAlgorithm *algorithm() const;

    /**
     * Returns a map of parameter sources. The keys are the child algorithm
     * parameter names, the values are the sources for that parameter.
     * \see setParameterSources()
     * \see addParameterSources()
     */
    QMap< QString, QList< QgsProcessingModelChildParameterSource > > parameterSources() const { return mParams; }

    /**
     * Sets the map of parameter \a sources. The keys are the child algorithm
     * parameter names, the values are the sources for that parameter.
     * \see parameterSources()
     * \see addParameterSources()
     */
    void setParameterSources( const QMap< QString, QList< QgsProcessingModelChildParameterSource > > &sources ) { mParams = sources; }

    /**
     * Adds a parameter source. The \a name argument should match
     * one of the child algorithm's parameter names, and the \a sources
     * argument is used to set the sources for that parameter.
     *
     * Any existing parameter sources with matching name will be replaced.
     * \see parameterSources()
     * \see setParameterSources()
     */
    void addParameterSources( const QString &name, const QList< QgsProcessingModelChildParameterSource > &source ) { mParams.insert( name, source ); }

    /**
     * Returns true if the child algorithm is active.
     * \see setActive()
     */
    bool isActive() const { return mActive; }

    /**
     * Sets whether the child algorithm is active.
     * \see isActive()
     */
    void setActive( bool active ) { mActive = active; }

    /**
     * Returns the list of child algorithms from the parent model on which this
     * algorithm is dependent. The returned list contains the id() of the
     * dependent algorithms.
     * \see setDependencies()
     */
    QStringList dependencies() const { return mDependencies; }

    /**
     * Sets the list of child algorithms from the parent model on which this
     * algorithm is dependent. The list should contain the id() of the
     * dependent algorithms.
     * \see dependencies()
     */
    void setDependencies( const QStringList &dependencies ) { mDependencies = dependencies; }

    /**
     * Returns true if the list of parameters for this algorithm should be collapsed
     * in the graphical modeler.
     * \see setParametersCollapsed()
     * \see outputsCollapsed()
     */
    bool parametersCollapsed() const { return mParametersCollapsed; }

    /**
     * Sets whether the list of parameters for this algorithm should be collapsed
     * in the graphical modeler.
     * \see parametersCollapsed()
     * \see setOutputsCollapsed()
     */
    void setParametersCollapsed( bool collapsed ) { mParametersCollapsed = collapsed; }

    /**
     * Returns true if the list of outputs for this algorithm should be collapsed
     * in the graphical modeler.
     * \see setParametersCollapsed()
     * \see parametersCollapsed()
     */
    bool outputsCollapsed() const { return mOutputsCollapsed; }

    /**
     * Sets whether the list of outputs for this algorithm should be collapsed
     * in the graphical modeler.
     * \see outputsCollapsed()
     * \see setParametersCollapsed()
     */
    void setOutputsCollapsed( bool collapsed ) { mOutputsCollapsed = collapsed; }

    /**
     * Returns the map of final model outputs which are generated by this child algorithm.
     * The keys are the output names from this child algorithm. Only outputs which are
     * part of the final outputs from the model are included in this map.
     * \see setModelOutputs()
     * \see modelOutput()
     */
    QMap<QString, QgsProcessingModelOutput> modelOutputs() const { return mModelOutputs; }

    /**
     * Returns the final model output with matching \a name. If no output
     * exists with the name, a new one will be created and returned.
     *
     * If child model outputs are altered by this method, QgsProcessingModelAlgorithm::updateDestinationParameters()
     * must be called on the parent model.
     *
     * \see modelOutputs()
     * \see setModelOutputs()
     */
    QgsProcessingModelOutput &modelOutput( const QString &name ) { return mModelOutputs[ name ]; }

    /**
     * Sets the map of final model \a outputs which are generated by this child algorithm.
     * Only outputs which are part of the final outputs from the model should be included in this map.
     *
     * If child model outputs are altered by this method, QgsProcessingModelAlgorithm::updateDestinationParameters()
     * must be called on the parent model.
     *
     * \see modelOutputs()
     */
    void setModelOutputs( const QMap<QString, QgsProcessingModelOutput> &outputs );

    /**
     * Removes an existing output from the final model outputs.
     *
     * QgsProcessingModelAlgorithm::updateDestinationParameters() must be called on the parent model.
     *
     * \see modelOutputs()
     * \since QGIS 3.2
     */
    bool removeModelOutput( const QString &name );

    /**
     * Saves this child to a QVariant.
     * \see loadVariant()
     */
    QVariant toVariant() const;

    /**
     * Loads this child from a QVariant.
     * \see toVariant()
     */
    bool loadVariant( const QVariant &child );

    /**
     * Attempts to convert the child to executable Python code.
     */
    QString asPythonCode() const;

  private:

    QString mId;

    QString mAlgorithmId;
    std::unique_ptr< QgsProcessingAlgorithm > mAlgorithm;

    QVariantMap mConfiguration;

    //! A map of parameter sources. Keys are algorithm parameter names.
    QMap< QString, QgsProcessingModelChildParameterSources > mParams;

    //! A map of ModelOutput for final model outputs generated by this child algorithm. Keys are output names from the child algorithm.
    QMap< QString, QgsProcessingModelOutput > mModelOutputs;

    bool mActive = true;

    //! List of child algorithms from the parent model on which this algorithm is dependent
    QStringList mDependencies;

    //! Whether list of parameters should be collapsed in the graphical modeler
    bool mParametersCollapsed = true;
    //! Whether list of outputs should be collapsed in the graphical modeler
    bool mOutputsCollapsed = true;

};

///@endcond

#endif // QGSPROCESSINGMODELCHILDALGORITHM_H
